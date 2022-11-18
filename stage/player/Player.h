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
	WorldTransform worldTransform_[7] = {};
	ViewProjection* viewProjection_ = nullptr;
	Model* model_ = nullptr;
	Model* modelKnight[7] = {};
	Input* input_ = nullptr;
	uint32_t texture_ = 0;
	const float CAMERA_DISTANCE = 30.0f;
	Direction direction_ = Front;
	Jamp jamp_;
	bool isTurn_=0;
	const int LERP_FLAME = 60;
	int nowFlame = 0;
	Vector3 larpVec[2]{};
	bool x = 0;

	uint16_t LorR = 0;// 1 = âEå¸Ç´,Å@0 = ç∂å¸Ç´ 
	float Rot = 0;
	void Move();
	bool Turn(float& pos1D, Direction nextDirection, float limitPos);
	Player() = default;
	~Player() = default;
public:
	static Player* GetInstance();

	void Initialize(Model* model1, Model* model2, Model* model3, Model* model4, Model* model5, Model* model6,
		ViewProjection* viewProjection);
	void Update();
	void Draw();
	void UpdateSpeed();
	Direction GetDirection() { return direction_; }

	void OnCollision(Collider* collider);
	const Vector3 GetWorldPosition() { return worldTransform_[0].translation_; }
	const Vector3 GetRadius() { return worldTransform_[0].scale_; }

	void ParentInitialize();

	void ParentUpdate();

	void ParentSetPosition();
};