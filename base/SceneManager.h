#pragma once

#include "SceneBase.h"
#include "AbstractSceneFactory.h"

class SceneManager
{
public:
	static SceneManager* GetInstance();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 次シーン予約
	/// </summary>
	/// <param name="sceneName">シーン名</param>
	void ChangeScene(const std::string& sceneName);

	void SetSceneFactory(AbstractSceneFactory* sceneFctr) { sceneFactory = sceneFctr; }
private:
	// 現在シーン
	SceneBase* scene = nullptr;
	// 次シーン
	SceneBase* nextScene = nullptr;
	// シーンファクトリ器
	AbstractSceneFactory* sceneFactory = nullptr;

	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = delete;
	void operator = (const SceneManager&) = delete;
};

