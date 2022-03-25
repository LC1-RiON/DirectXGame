#include "SceneManager.h"

#include <cassert>
SceneManager::~SceneManager()
{
	// シーン終了
	scene->Finalize();
	delete scene;
}

SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;

	return &instance;
}

void SceneManager::Update()
{
	// 次シーンがあるとき
	if (nextScene) {
		// シーンリセット
		if (scene) {
			scene->Finalize();
			delete scene;
		}
		// シーン切替
		scene = nextScene;
		nextScene = nullptr;

		// 新シーン初期化
		scene->Initialize();
	}
	scene->Update();
}

void SceneManager::Draw()
{
	scene->Draw();
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	assert(sceneFactory);
	assert(nextScene == nullptr);

	// 次シーン生成
	nextScene = sceneFactory->CreateScene(sceneName);
}
