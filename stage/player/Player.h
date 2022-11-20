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
	enum { Root, Head, Chest, HandLeft, HandRight, FootLeft, FootRight };

	DebugText* debugText_ = nullptr;
	std::vector<WorldTransform> worldTransform_;
	std::vector<Model*> modelKnight;
	ViewProjection* viewProjection_ = nullptr;
	Input* input_ = nullptr;
	uint32_t texture_ = 0;
	const float CAMERA_DISTANCE = 30.0f;
	Direction direction_ = Front;
	Jamp jamp_;
	bool isTurn_ = 0;
	const int LERP_FLAME = 60;
	int nowFlame = 0;
	Vector3 larpVec[2]{};

	uint16_t LorR = 0;// 1 = 右向き,　0 = 左向き 
	float Rot = 0;
	bool walkFlag = true;
	float walkPos = 0.0f;
	int walkTimer = 5.0f;
	bool isAttack = false;
	bool isUp = false;
	float ATrot = 0.0f;
	void Move();
	bool Turn(float& pos1D, Direction nextDirection, float limitPos);
	Player() = default;
	~Player() = default;
	float DirectionToRadian();
	void WalkMotion();			//歩くモーション
	void AttackMotion();		//攻撃のモーション
public:
	static Player* GetInstance();

	void Initialize(ViewProjection* viewProjection);
	void Update();
	void Draw();
	Direction GetDirection() { return direction_; }

	void OnCollision(Collider* collider);
	const Vector3 GetWorldPosition() { return worldTransform_[0].translation_; }
	const Vector3 GetRadius() { return worldTransform_[0].scale_; }
};