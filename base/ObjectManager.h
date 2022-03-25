#pragma once

#include "Object3d.h"
#include <memory>

class ObjectManager
{
public:
	void Update();

	void Draw();

	/// <summary>
	/// オブジェクト追加
	/// </summary>
	/// <param name="obj">オブジェクト</param>
	std::weak_ptr<Object3d> AddObject(std::shared_ptr<Object3d> obj);

private:
	// オブジェクトリスト
	std::vector<std::shared_ptr<Object3d>> objects;
};

