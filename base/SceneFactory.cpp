#include "SceneFactory.h"
#include "GameScene.h"
#include "TitleScene.h"

SceneBase* SceneFactory::CreateScene(const std::string& sceneName)
{
    // 次シーンの生成
    SceneBase* newScene = nullptr;

    if (sceneName == "TITLE") {
    newScene = new TitleScene();
    }
    else if (sceneName == "GAMEPLAY") {
        newScene = new GameScene();
    }

    return newScene;
}
