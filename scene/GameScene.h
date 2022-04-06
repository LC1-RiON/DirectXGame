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

	Model* model_1 = nullptr;
	Model* model_2 = nullptr;
	Model* model_3 = nullptr;

	std::shared_ptr<Object3d> floor;
	std::shared_ptr<Object3d> object1;
	std::shared_ptr<Object3d> object2;

	std::unique_ptr<ObjectManager> objectManager;

	int playerMode = 1;
};

