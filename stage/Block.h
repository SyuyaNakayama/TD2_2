#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "scene.h"
#include <vector>
#include <Model.h>

// 1方向分のブロック情報
class Block
{
private:
	std::vector<WorldTransform> worldTransforms_;
	Model* model_ = nullptr;
	Direction direction_;
public:
	void Initialize(Direction direction);
	void Draw(ViewProjection viewProjection);
	// pos : 各面を正面から見た時の左下からの距離
	void Add(Vector2 pos, Vector3 rad = { 1,1,1 });
};