#pragma once

#include "SceneBase.h"
#include "AbstractSceneFactory.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���V�[���\��
	/// </summary>
	/// <param name="sceneName">�V�[����</param>
	void ChangeScene(const std::string& sceneName);

	void SetSceneFactory(AbstractSceneFactory* sceneFctr) { sceneFactory = sceneFctr; }
private:
	// ���݃V�[��
	SceneBase* scene = nullptr;
	// ���V�[��
	SceneBase* nextScene = nullptr;
	// �V�[���t�@�N�g����
	AbstractSceneFactory* sceneFactory = nullptr;

	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = delete;
	void operator = (const SceneManager&) = delete;
};

