#pragma once
#include "collider/Collider.h"
#include "WorldTransform.h"
#include "Model.h"
#include "TextureManager.h"
#include "Input.h"
#include "ViewProjection.h"
#include <memory>
#include "DebugText.h"

class Player :public Collider
{
public:
	enum Direction { Front, Right, Back, Left };
private:
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	uint32_t texture_ = 0;
	Vector3 spd_{};
	const float CAMERA_DISTANCE = 70.0f;
	Direction direction_ = Front;
	float poleRadius_ = 0;

	void Move();
public:
	Player() = default;
	~Player() = default;
	static std::unique_ptr<Player> GetInstance();
	void Initialize(ViewProjection* viewProjection,float poleRad);
	void Update();
	void Draw();
	void UpdateSpeed();
	void DirectionChange();
	Direction GetDirection() { return direction_; }

	const Vector3 GetPosition() { return worldTransform_.translation_; }

	void OnCollision(Collider* collider);
	const Vector3 GetWorldPosition() { return worldTransform_.translation_ + spd_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
};