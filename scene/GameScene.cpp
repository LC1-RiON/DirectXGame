#include "GameScene.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "Audio.h"
#include "Input.h"
#include "DebugText.h"
// Git作動テスト用コメント
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
	// 3Dオブジェクト生成
	std::weak_ptr<Object3d> floorWP = objectManager->AddObject(Object3d::Create(model_1));
	floor = floorWP.lock();
	std::weak_ptr<Object3d> object1WP = objectManager->AddObject(Object3d::Create(model_2));
	object1 = object1WP.lock();
	std::weak_ptr<Object3d> object2WP = objectManager->AddObject(Object3d::Create(model_2));
	object2 = object2WP.lock();
	// オブジェクト位置調整
	object1->SetPosition({ -5,0,-5 });
	object2->SetPosition({ +5,0,+5 });

	// 音声読み込み
	Audio::GetInstance()->LoadWave("Alarm01.wav");

	// 音声再生
	Audio::GetInstance()->PlayWave("Alarm01.wav");
}

void GameScene::Finalize()
{
	delete sprite;
	delete model_1;
	delete model_2;
}

void GameScene::Update()
{
	// Git作動テスト用コメント
	Input* input = Input::GetInstance();

	if (input->PushKey(DIK_0)) // 数字の0キーが押されていたら
	{
		OutputDebugStringA("Hit 0\n");  // 出力ウィンドウに「Hit 0」と表示
	}

	if (input->TriggerKey(DIK_RETURN)) {
		SceneManager::GetInstance()->ChangeScene("TITLE");
	}

	// X座標,Y座標を指定して表示
	DebugText::GetInstance()->Print("Hello,DirectX!!", 200, 100);
	// X座標,Y座標,縮尺を指定して表示
	DebugText::GetInstance()->Print("Nihon Kogakuin", 200, 200, 2.0f);

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
