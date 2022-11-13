#pragma once
#include "collider/Collider.h"
#include "WorldTransform.h"
#include "Model.h"
#include "TextureManager.h"
#include "input.h"
#include "ViewProjection.h"
#include <memory>

class Player :public Collider
{
public:
	enum Direction { Front, Right, Back, Left };
private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	uint32_t texture_ = 0;
	Vector3 spd_{};
	const float CAMERA_DISTANCE = 70.0f;
	Direction direction_ = Front;

	void Move();
public:
	Player() = default;
	~Player() = default;
	static std::unique_ptr<Player> GetInstance();
	void Initialize(ViewProjection& viewProjection);
	void Update();
	void Draw();
	void UpdateSpeed();
	void DirectionChange(uint32_t endDis);
	Direction GetDirection() { return direction_; }

	void OnCollision(Collider* collider);
	const Vector3 GetWorldPosition() { return worldTransform_.translation_ + spd_; }
	const Vector3 GetRadius() { return worldTransform_.scale_; }
};