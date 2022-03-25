#include "OurUniqueGame.h"
#include "SceneFactory.h"

void OurUniqueGame::Initialize()
{
    // ベースクラス初期化
    Framework::Initialize();
#pragma region シーン初期化

    // シーンファクトリ生成、マネージャにセット
    sceneFactory = std::make_unique<SceneFactory>();
    SceneManager::GetInstance()->SetSceneFactory(sceneFactory.get());

    SceneManager::GetInstance()->ChangeScene("TITLE");

#pragma endregion シーン初期化
}

void OurUniqueGame::Finalize()
{
    // 各ポインタ解放

    // ベースクラス終了
    Framework::Finalize();
}

void OurUniqueGame::Update()
{
    // ベースクラス更新
    Framework::Update();
}

void OurUniqueGame::Draw()
{
    // ベースクラス描画
    Framework::Draw();
}
