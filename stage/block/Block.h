#pragma once
#include "Model.h"
#include "scene.h"
#include <vector>

// 1�������̃u���b�N���
class Block
{
private:
	std::vector<WorldTransform> worldTransforms_;
	Model* model_ = nullptr;
	Direction direction_;
	float Rot = 0.0f;
public:
	~Block() { delete model_; }
	void Initialize(Direction direction);
	void Draw(ViewProjection viewProjection);
	// pos : �e�ʂ𐳖ʂ��猩�����̍�������̋���
	void Add(Vector2 pos, Vector3 rad = { 1,1,1 });
};