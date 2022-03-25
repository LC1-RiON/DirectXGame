#pragma once

#include"Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Sprite.h"
#include "DebugText.h"
#include "Audio.h"
#include "SceneManager.h"
#include "AbstractSceneFactory.h"

#include <memory>

class Framework
{
public:
	/// <summary>
	/// 実行
	/// </summary>
	void Run();

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	virtual bool GetEnd() { return endRequest; }

protected:
	WinApp* winApp = nullptr;
	Input* input = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Audio* audio = nullptr;
	DebugText* debugText = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Sprite* sprite = nullptr;
	std::unique_ptr<AbstractSceneFactory> sceneFactory;
	bool endRequest = false;
};
