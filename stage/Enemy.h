#pragma once
#include "collider/Collider.h"
#include "WorldTransform.h"
#include "Model.h"
#include "TextureManager.h"
#include "ViewProjection.h"

class Enemy :public Collider
{
private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t texture_ = 0;

	void Move();
public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);

	void OnCollision(Collider* collider) {};
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
};