#pragma once
#include "SceneBase.h"
#include "Sprite.h"
#include "Object3d.h"
#include "ObjectManager.h"

#include <memory>
class GameScene : public SceneBase
{
public:
	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;

private:
	Sprite* sprite;

	Model* modelFloor = nullptr;
	Model* modelPlayer = nullptr;
	Model* modelEnemy1 = nullptr;
	Model* modelFlag = nullptr;

	std::shared_ptr<Object3d> floor;
	std::shared_ptr<Object3d> object1;
	std::shared_ptr<Object3d> object2;
	std::shared_ptr<Object3d> goal;

	std::unique_ptr<ObjectManager> objectManager;

	int playerMode = 1;

	const float rotUNIT = 1;
	float rotX = 0;
	float rotY = 0;
	float rotZ = 0;

	int score = 0;
};

