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
	model_1 = Model::LoadFromOBJ("ground");
	model_2 = Model::LoadFromOBJ("triangle_mat");
	model_3 = Model::LoadFromOBJ("gortopus");
	// 3Dオブジェクト生成
	std::weak_ptr<Object3d> floorWP = objectManager->AddObject(Object3d::Create(model_1));
	floor = floorWP.lock();
	std::weak_ptr<Object3d> object1WP = objectManager->AddObject(Object3d::Create(model_2));
	object1 = object1WP.lock();
	std::weak_ptr<Object3d> object2WP = objectManager->AddObject(Object3d::Create(model_3));
	object2 = object2WP.lock();
	// オブジェクト位置調整
	object1->SetPosition({ 0,0,-5 });
	object2->SetPosition({ 0,0,+5 });

	object2->SetRotation({ 0,180,0 });

	// プレイヤー後方にカメラを配置
	XMFLOAT3 eye = object1->GetPosition();
	eye.y += 10.0f;
	eye.z -= 10.0f;
	Object3d::SetEye(eye);
	XMFLOAT3 target = Object3d::GetTarget();
	target.y += 10.0f;
	target.z -= 10.0f;
	Object3d::SetTarget(target);

	// 音声読み込み
	Audio::GetInstance()->LoadWave("Alarm01.wav");

	// 音声再生
	//Audio::GetInstance()->PlayWave("Alarm01.wav");
}

void GameScene::Finalize()
{
	delete sprite;
	delete model_1;
	delete model_2;
	delete model_3;
}

void GameScene::Update()
{
	Input* input = Input::GetInstance();

	// WASDによる移動操作
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A)) {
		XMFLOAT3 pos = object1->GetPosition();
		XMFLOAT3 target = Object3d::GetTarget();
		if (input->PushKey(DIK_W)) {
			pos.z += 1.0f;
			target.z += 1.0f;
		}
		if (input->PushKey(DIK_S)) {
			pos.z -= 1.0f;
			target.z -= 1.0f;
		}
		if (input->PushKey(DIK_D)) {
			pos.x += 1.0f;
			target.x += 1.0f;
		}
		if (input->PushKey(DIK_A)) {
			pos.x -= 1.0f;
			target.x -= 1.0f;
		}
		object1->SetPosition(pos);
		Object3d::SetTarget(target);
	}

	// 左右の自機回転
	if (input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {
		XMFLOAT3 rot = object1->GetRotation();
		if (input->PushKey(DIK_RIGHT)) {
			rot.y += 1;
		}
		if (input->PushKey(DIK_LEFT)) {
			rot.y -= 1;
		}
		object1->SetRotation(rot);
	}

	// プレイヤーにカメラ追従
	XMFLOAT3 eye = object1->GetPosition();
	eye.y += 10.0f;
	eye.z -= 10.0f;
	Object3d::SetEye(eye);

	// カメラ追従、自機回転対応型
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {
		if (input->PushKey(DIK_UP)) {

		}
		if (input->PushKey(DIK_DOWN)) {

		}
		if (input->PushKey(DIK_RIGHT)) {

		}
		if (input->PushKey(DIK_LEFT)) {

		}
	}

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
