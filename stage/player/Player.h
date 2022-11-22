#pragma once
#include "collider/Collider.h"
#include "Input.h"
#include "DebugText.h"
#include "../stage/Jamp.h"
#include "Model.h"
#include "scene.h"
#include "timer/Timer.h"

class Player :public Collider
{
private:
	enum { Root, Head, Chest, HandLeft, HandRight, FootLeft, FootRight };

	DebugText* debugText_ = DebugText::GetInstance();
	std::vector<WorldTransform> worldTransform_;
	std::vector<Model*> modelKnight;
	ViewProjection* viewProjection_ = nullptr;
	Input* input_ = Input::GetInstance();
	uint32_t texture_ = 0;
	const float CAMERA_DISTANCE = 30.0f;
	Direction direction_ = Front;
	Jamp jamp_;
	bool isTurn_ = 0;
	const int LERP_FLAME = 60;
	int nowFlame = 0;
	Vector3 larpVec[2]{};
	Timer walkTimer_ = 10;

	bool isHit = false; // falseのときに当たり判定が発生
	Timer hitTimer = 100;
	bool isDraw = true;
	Timer drawInterval = 5;
	int hp_ = 10;
	uint16_t LorR = 0;// 1 = 右向き,　0 = 左向き 
	float Rot = 0;
	bool walkFlag = true;
	float walkPos = 0.0f;
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
	std::vector<WorldTransform> GetWorldTransforms() { return worldTransform_; }
	void SetWorldTransforms(std::vector<WorldTransform> worldTransforms) { worldTransform_ = worldTransforms; }

	void OnCollision(Collider* collider);
	const Vector3 GetWorldPosition() { return Vector3(worldTransform_[1].matWorld_.m[3][0], worldTransform_[1].matWorld_.m[3][1], worldTransform_[1].matWorld_.m[3][2]); }
	const Vector3 GetRadius() { return Vector3(2.0f, 3.0f, 3.0f); }
};

class PlayerAttack : Collider
{
public:
	Player* player_ = Player::GetInstance();

public:
	void OnCollision(Collider* collider) {}
	const Vector3 GetWorldPosition() { return player_->GetWorldPosition() + Vector3(-1.0f, 0, 0); }
	const Vector3 GetRadius() { return Vector3(3.0f, 3.0f, 3.0f); }
};