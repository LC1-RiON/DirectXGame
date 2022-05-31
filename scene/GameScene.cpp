#include "GameScene.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
#include <time.h>

using namespace DirectX;

void GameScene::Initialize()
{
	srand(time(NULL));
	// スプライト共通テクスチャ読み込み
	SpriteCommon::GetInstance()->LoadTexture(1, L"Resources/playscene.png");
	SpriteCommon::GetInstance()->LoadTexture(2, L"Resources/complete.png");
	//spriteCommon->LoadTexture(2, L"Resources/house.png");

	// スプライトの生成
	sprite = Sprite::Create(1, { 0,0 }, false, false);
	spriteComp = Sprite::Create(2, { 0,0 }, false, false);

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
	goal->SetPosition(XMFLOAT3(rand() % 101 - 50, 0, rand() % 101 - 50));

	object2->SetRotation({ 0,180,0 });

	object2->SetScale(XMFLOAT3(0.5f, 0.5f, 0.5f));
	goal->SetScale(XMFLOAT3(5.0f, 5.0f, 5.0f));

	// プレイヤー視点にカメラを配置
	XMFLOAT3 pos = object1->GetPosition();
	XMFLOAT3 rot = object1->GetRotation();
	XMFLOAT3 eye = pos;
	eye.x += sinf(XMConvertToRadians(rot.y)) * 1.0f;
	eye.y += 10.0f;
	eye.z += cosf(XMConvertToRadians(rot.y)) * 1.0f;
	Object3d::SetEye(eye);
	XMFLOAT3 target = pos;
	target.x += sinf(XMConvertToRadians(rot.y)) * 10.0f;
	target.y += 10.0f;
	target.z += cosf(XMConvertToRadians(rot.y)) * 10.0f;
	Object3d::SetTarget(target);

	// 音声読み込み
	Audio::GetInstance()->LoadWave("Alarm01.wav");	

	// 音声再生
	//Audio::GetInstance()->PlayWave("Alarm01.wav");
}

void GameScene::Finalize()
{
	delete sprite;
	delete spriteComp;
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
	}
	object1->SetPosition(pos);

	// 左右の自機回転、左シフトで3倍速
	if (input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {
		if (input->PushKey(DIK_RIGHT)) {
			if (input->PushKey(DIK_LSHIFT))
				rot.y += rotUNIT * 2.0f;
			rot.y += rotUNIT;
		}
		if (input->PushKey(DIK_LEFT)) {
			if (input->PushKey(DIK_LSHIFT))
				rot.y -= rotUNIT * 2.0f;
			rot.y -= rotUNIT;
		}
	}
	object1->SetRotation(rot);

	// プレイヤーにカメラ追従
	XMFLOAT3 eye = object1->GetPosition();
	eye.x += sinf(XMConvertToRadians(rot.y)) * 1.0f;
	eye.y += 10.0f;
	eye.z += cosf(XMConvertToRadians(rot.y)) * 1.0f;
	Object3d::SetEye(eye);
	XMFLOAT3 target = object1->GetPosition();
	target.x += sinf(XMConvertToRadians(rot.y)) * 10.0f;
	target.y += 10.0f;
	target.z += cosf(XMConvertToRadians(rot.y)) * 10.0f;
	Object3d::SetTarget(target);

	// SPACEキーでモードチェンジ
	if (input->TriggerKey(DIK_SPACE)) {
		playerMode++;
		if (playerMode >= 4)
			playerMode = 1;
	}

	// ゴール判定
	XMFLOAT3 pPos = object1->GetPosition();
	XMFLOAT3 gPos = goal->GetPosition();
	float range = sqrtf(powf(pPos.x - gPos.x, 2) + powf(pPos.z - gPos.z, 2));
	if (range <= 5.0f) {
		score++;
		goal->SetPosition(XMFLOAT3(rand() % 101 - 50, 0, rand() % 101 - 50));
	}

	//if (input->PushKey(DIK_0)) // 数字の0キーが押されていたら
	//{
	//	OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
	//}

	// Rキーでリセット
	if (input->TriggerKey(DIK_R)) {
		SceneManager::GetInstance()->ChangeScene("GAMEPLAY");
	}

	if (input->TriggerKey(DIK_RETURN)) {
		SceneManager::GetInstance()->ChangeScene("TITLE");
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

	// 特定スコア到達
	if (score >= 10) {
		spriteComp->Draw();
	}

	char numScore[10] = {};
	sprintf_s(numScore, 10,"%d", score);

	DebugText::GetInstance()->Print("SCORE : ", 1100, 150);
	DebugText::GetInstance()->Print(numScore, 1170, 150);

	// プレイヤーモード毎の表記
	//switch (playerMode) {
	//case 1:
	//	DebugText::GetInstance()->Print("MODE BAT", 200, 100);
	//	break;
	//case 2:
	//	DebugText::GetInstance()->Print("MODE SNAKE", 200, 100);
	//	break;
	//case 3:
	//	DebugText::GetInstance()->Print("MODE DOG", 200, 100);
	//	break;
	//}
}
