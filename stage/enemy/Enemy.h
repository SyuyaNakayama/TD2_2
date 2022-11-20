#pragma once
#include "collider/Collider.h"
#include "WorldTransform.h"
#include "Model.h"
#include "TextureManager.h"
#include "ViewProjection.h"
#include "Input.h"
#include "DebugText.h"

class Enemy :public Collider
{
private:
	const static uint16_t modelNum = 12;
	WorldTransform worldTransform_[modelNum] = {};
	Model* model_ = nullptr;
	Model* modelDoragon[modelNum] = {};
	uint32_t texture_ = 0;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	float Rot = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float s = 0.0f;
	void Move();
public:
	void Initialize();
	void Update();
	void Draw(ViewProjection viewProjection);

	void OnCollision(Collider* collider) {};
	const Vector3 GetWorldPosition() { return worldTransform_[0].translation_; }
	const Vector3 GetRadius() { return worldTransform_[0].scale_; }

	void ParentInitialize();

	void ParentUpdate();

	void ParentSetPosition();
};