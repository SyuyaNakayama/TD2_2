#pragma once
#include "collider/Collider.h"
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include "scene.h"
#include "Jamp.h"

class Player :public Collider
{
private:
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	uint32_t texture_ = 0;
	const float CAMERA_DISTANCE = 50.0f;
	Direction direction_ = Front;
	Jamp jamp_;

	void Move();
	void Turn(float& pos1D, Direction nextDirection, float limitPos);
public:
	Player() = default;
	~Player() = default;
	static Player* GetInstance();
	void Initialize(ViewProjection* viewProjection);
	void Update();
	void Draw();
	void UpdateSpeed();
	Direction GetDirection() { return direction_; }

	void OnCollision(Collider* collider);
	const Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
};