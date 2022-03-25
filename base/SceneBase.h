#pragma once

class SceneManager;

class SceneBase
{
public:
	virtual ~SceneBase() = default;

	virtual void Initialize() = 0;

	virtual void Finalize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;
};

