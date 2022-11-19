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

	uint16_t LorR = 0;// 1 = 右向き,　0 = 左向き 
	float Rot = 0;
	bool walkFlag = true;
	float walkPos = 0.0f;
	float walkTimer = 5.0f;
	bool isAttack = false;
	bool isUp = false;
	float ATrot = 0.0f;
	void Move();
	bool Turn(float& pos1D, Direction nextDirection, float limitPos);
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
	const Vector3 GetWorldPosition() { return worldTransform_[0].translation_; }
	const Vector3 GetRadius() { return worldTransform_[0].scale_; }

	void ParentInitialize();

	void ParentUpdate();

	void ParentSetPosition();	//各パーツの初期位置、左右反転

	void WalkMotion();			//歩くモーション

	void AttackMotion();		//攻撃のモーション
};