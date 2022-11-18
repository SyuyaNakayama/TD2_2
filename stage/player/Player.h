#pragma once
#include "collider/Collider.h"
#include "Input.h"
#include "DebugText.h"
#include "../stage/Jamp.h"
#include "WorldTransform.h"
#include "Model.h"
#include "ViewProjection.h"
#include "scene.h"

class Player :public Collider
{
private:
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	uint32_t texture_ = 0;
	const float CAMERA_DISTANCE = 30.0f;
	Direction direction_ = Front;
	Jamp jamp_;
	bool isTurn_;
	const int LERP_FLAME = 60;
	int nowFlame = 0;

	void Move();
	void Turn(float& pos1D, Direction nextDirection, float limitPos);
	Player() = default;
	~Player() = default;
public:
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