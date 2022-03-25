#pragma once
#include "AbstractSceneFactory.h"
class SceneFactory :
    public AbstractSceneFactory
{
public:
	/// <summary>
	/// シーン生成
	/// </summary>
	/// <paramname="sceneName">シーン名</param>
	/// <returns>生成したシーン</returns>
	SceneBase* CreateScene(const std::string& sceneName) override;
};
