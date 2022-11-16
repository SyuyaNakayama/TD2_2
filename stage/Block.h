#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "scene.h"
#include <vector>
#include <Model.h>

// 1�������̃u���b�N���
class Block
{
private:
	std::vector<WorldTransform> worldTransforms_;
	Model* model_ = nullptr;
	Direction direction_;
public:
	void Initialize(Direction direction);
	void Draw(ViewProjection viewProjection);
	// pos : �e�ʂ𐳖ʂ��猩�����̍�������̋���
	void Add(Vector2 pos, Vector3 rad = { 1,1,1 });
};