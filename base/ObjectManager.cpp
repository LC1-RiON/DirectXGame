#include "ObjectManager.h"

void ObjectManager::Update()
{
	for (std::shared_ptr<Object3d>& object : objects) {
		object->Update();
	}
}

void ObjectManager::Draw()
{
	for (std::shared_ptr<Object3d>& object : objects) {
		object->Draw();
	}
}

std::weak_ptr<Object3d> ObjectManager::AddObject(std::shared_ptr<Object3d> obj)
{
	// �I�u�W�F�N�g���X�g�ɒǉ�
	objects.push_back(std::move(obj));

	return objects.back();
}
