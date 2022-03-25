#include "SceneManager.h"

#include <cassert>
SceneManager::~SceneManager()
{
	// �V�[���I��
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
	// ���V�[��������Ƃ�
	if (nextScene) {
		// �V�[�����Z�b�g
		if (scene) {
			scene->Finalize();
			delete scene;
		}
		// �V�[���ؑ�
		scene = nextScene;
		nextScene = nullptr;

		// �V�V�[��������
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

	// ���V�[������
	nextScene = sceneFactory->CreateScene(sceneName);
}
