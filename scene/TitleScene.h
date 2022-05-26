#pragma once

#include "SceneBase.h"
#include "Sprite.h"
#include "Object3d.h"

class TitleScene : public SceneBase
{
public:
	void Initialize() override;

	void Finalize() override;

	void Update() override;

	void Draw() override;

private:
	Sprite* sprite = nullptr;

	int count = 0;
};

