#pragma once
#include "collider/Collider.h"
#include "WorldTransform.h"
#include "Model.h"
#include "TextureManager.h"
#include "Input.h"
#include "ViewProjection.h"
#include <memory>
#include "DebugText.h"
#include "scene.h"
#include "Jamp.h"

class Player :public Collider
{
private:
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransform_[7] = {};
	ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	Model* modelKnight[7] = {};
	Input* input_ = nullptr;
	uint32_t texture_ = 0;
	Vector3 spd_{};
	const float CAMERA_DISTANCE = 50.0f;
	Direction direction_ = Front;
	Jamp jamp_;
	uint16_t LorR = 0;// 1 = âEå¸Ç´,Å@0 = ç∂å¸Ç´ 
	float Rot = 0;
	void Move();
	void Turn(float& pos1D, Direction nextDirection, float limitPos);
public:
	Player() = default;
	~Player() = default;
	static std::unique_ptr<Player> GetInstance();
	void Initialize(Model* model1, Model* model2, Model* model3, Model* model4, Model* model5, Model* model6,
		ViewProjection* viewProjection);
	void Update();
	void Draw();
	void UpdateSpeed();
	Direction GetDirection() { return direction_; }

	const Vector3 GetPosition() { return worldTransform_[0].translation_; }

	void OnCollision(Collider* collider);
	const Vector3 GetWorldPosition() { return worldTransform_[0].translation_ + spd_; }
	const Vector3 GetRadius() { return worldTransform_[0].scale_; }

	void ParentInitialize();

	void ParentUpdate();

	void ParentSetPosition();
};