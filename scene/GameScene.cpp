#include "GameScene.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"

using namespace DirectX;

void GameScene::Initialize()
{
	// スプライト共通テクスチャ読み込み
	SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/playscene.png");
	//spriteCommon->LoadTexture(2, L"Resources/house.png");

	// スプライトの生成
	sprite = Sprite::Create(1, { 0,0 }, false, false);

	// オブジェクトマネージャ生成
	objectManager = std::make_unique<ObjectManager>();

	// .objからモデルデータ読み込み
	modelFloor = Model::LoadFromOBJ("ground");
	modelPlayer = Model::LoadFromOBJ("triangle_mat");
	modelEnemy1 = Model::LoadFromOBJ("gortopus");
	modelFlag = Model::LoadFromOBJ("flag");
	// 3Dオブジェクト生成
	std::weak_ptr<Object3d> floorWP = objectManager->AddObject(Object3d::Create(modelFloor));
	floor = floorWP.lock();
	std::weak_ptr<Object3d> object1WP = objectManager->AddObject(Object3d::Create(modelPlayer));
	object1 = object1WP.lock();
	std::weak_ptr<Object3d> object2WP = objectManager->AddObject(Object3d::Create(modelEnemy1));
	object2 = object2WP.lock();
	std::weak_ptr<Object3d> goalWP = objectManager->AddObject(Object3d::Create(modelFlag));
	goal = goalWP.lock();
	// オブジェクト位置調整
	object1->SetPosition({ 0,0,-5 });
	object2->SetPosition({ 0,0,+5 });
	goal->SetPosition({ 30,0,50 });

	object2->SetRotation({ 0,180,0 });

	object2->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
	goal->SetScale(XMFLOAT3(5.0f, 5.0f, 5.0f));

	// プレイヤー後方にカメラを配置
	XMFLOAT3 pos = object1->GetPosition();
	XMFLOAT3 eye = pos;
	XMFLOAT3 rot = object1->GetRotation();
	eye.x -= sinf(XMConvertToRadians(rot.y)) * 10.0f;
	eye.y += 10.0f;
	eye.z -= cosf(XMConvertToRadians(rot.y)) * 10.0f;
	Object3d::SetEye(eye);
	Object3d::SetTarget(XMFLOAT3(pos.x, pos.y + 10.0f, pos.z));

	// 音声読み込み
	Audio::GetInstance()->LoadWave("Alarm01.wav");

	// 音声再生
	//Audio::GetInstance()->PlayWave("Alarm01.wav");
}

void GameScene::Finalize()
{
	delete sprite;
	delete modelFloor;
	delete modelPlayer;
	delete modelEnemy1;
	delete modelFlag;
}

void GameScene::Update()
{
	Input* input = Input::GetInstance();

	// 自機移動準備
	XMFLOAT3 pos = object1->GetPosition();
	XMFLOAT3 rot = object1->GetRotation();
	// WASDによる移動操作
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A)) {
		if (input->PushKey(DIK_W)) {
			pos.x += sinf(XMConvertToRadians(rot.y));
			pos.z += cosf(XMConvertToRadians(rot.y));
		}
		if (input->PushKey(DIK_S)) {
			pos.x -= sinf(XMConvertToRadians(rot.y));
			pos.z -= cosf(XMConvertToRadians(rot.y));
		}
		if (input->PushKey(DIK_D)) {
			pos.x += cosf(XMConvertToRadians(rot.y));
			pos.z -= sinf(XMConvertToRadians(rot.y));
		}
		if (input->PushKey(DIK_A)) {
			pos.x -= cosf(XMConvertToRadians(rot.y));
			pos.z += sinf(XMConvertToRadians(rot.y));
		}
		object1->SetPosition(pos);
		Object3d::SetTarget(XMFLOAT3(pos.x, pos.y + 10.0f, pos.z));
	}

	// 左右の自機回転
	if (input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {
		if (input->PushKey(DIK_RIGHT)) {
			rot.y += rotUNIT;
		}
		if (input->PushKey(DIK_LEFT)) {
			rot.y -= rotUNIT;
		}
		object1->SetRotation(rot);
	}

	// プレイヤーにカメラ追従
	XMFLOAT3 eye = object1->GetPosition();
	eye.x -= sinf(XMConvertToRadians(rot.y)) * 10.0f;
	eye.y += 10.0f;
	eye.z -= cosf(XMConvertToRadians(rot.y)) * 10.0f;
	Object3d::SetEye(eye);

	// SPACEキーでモードチェンジ
	if (input->TriggerKey(DIK_SPACE)) {
		playerMode++;
		if (playerMode >= 4)
			playerMode = 1;
	}

	//if (input->PushKey(DIK_0)) // 数字の0キーが押されていたら
	//{
	//	OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
	//}

	if (input->TriggerKey(DIK_RETURN)) {
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	// プレイヤーモード毎の表記
	switch (playerMode) {
	case 1:
		DebugText::GetInstance()->Print("MODE BAT", 200, 100);
		break;
	case 2:
		DebugText::GetInstance()->Print("MODE SNAKE", 200, 100);
		break;
	case 3:
		DebugText::GetInstance()->Print("MODE DOG", 200, 100);
		break;
	}

	// 3Dオブジェクト更新
	objectManager->Update();

	// スプライト更新
	sprite->Update();
}

void GameScene::Draw()
{
	// スプライト描画前処理
	SpriteCommon::GetInstance()->PreDraw();

	/// <summary>
	/// スプライト描画処理の追加位置
	/// </summary>

	// スプライト描画
	sprite->Draw();

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw();

	/// <summary>
	/// 3Dオブジェクト描画処理の追加位置
	/// </summary>

	objectManager->Draw();

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	// スプライト描画前処理
	SpriteCommon::GetInstance()->PreDraw();

	/// <summary>
	/// スプライト描画処理の追加位置
	/// </summary>
}
