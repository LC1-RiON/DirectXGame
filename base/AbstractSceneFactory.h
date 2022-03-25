#pragma once

#include "SceneBase.h"
#include <string>
class AbstractSceneFactory
{
public:
	virtual ~AbstractSceneFactory() = default;
	/// <summary>
	/// �V�[������
	/// </summary>
	/// <returns>���������V�[��</returns>
	virtual SceneBase* CreateScene(const std::string& sceneName) = 0;
};

