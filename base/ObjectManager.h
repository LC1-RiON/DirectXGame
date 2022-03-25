#pragma once

#include "Object3d.h"
#include <memory>

class ObjectManager
{
public:
	void Update();

	void Draw();

	/// <summary>
	/// �I�u�W�F�N�g�ǉ�
	/// </summary>
	/// <param name="obj">�I�u�W�F�N�g</param>
	std::weak_ptr<Object3d> AddObject(std::shared_ptr<Object3d> obj);

private:
	// �I�u�W�F�N�g���X�g
	std::vector<std::shared_ptr<Object3d>> objects;
};

