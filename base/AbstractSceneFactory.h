#pragma once

#include "SceneBase.h"
#include <string>
class AbstractSceneFactory
{
public:
	virtual ~AbstractSceneFactory() = default;
	/// <summary>
	/// シーン生成
	/// </summary>
	/// <returns>生成したシーン</returns>
	virtual SceneBase* CreateScene(const std::string& sceneName) = 0;
};

