#pragma once
#include "AbstractSceneFactory.h"
class SceneFactory :
    public AbstractSceneFactory
{
public:
	/// <summary>
	/// �V�[������
	/// </summary>
	/// <paramname="sceneName">�V�[����</param>
	/// <returns>���������V�[��</returns>
	SceneBase* CreateScene(const std::string& sceneName) override;
};
