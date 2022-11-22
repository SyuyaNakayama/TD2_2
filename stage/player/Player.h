#pragma once
#include "collider/Collider.h"
#include "Input.h"
#include "DebugText.h"
#include "../stage/Jamp.h"
#include "Model.h"
#include "scene.h"
#include "timer/Timer.h"

class PlayerAttack :public Collider
{
private:
	WorldTransform* playerWorldTransform_ = nullptr;
	bool isUp = false;
	float ATrot = 0.0f;
	bool isAttack = false;
	Vector3 GetPositionFromMatrix4(Matrix4 matWorld) { return Vector3(matWorld.m[3][0], matWorld.m[3][1], matWorld.m[3][2]); }

public:
	void Initialize(WorldTransform* playerWorldTransform) { playerWorldTransform_ = playerWorldTransform; }
	void Motion();	//攻撃のモーション
	bool IsAttack() { return isAttack; }
	void OnCollision(Collider* collider) {}
	const Vector3 GetWorldPosition() { return GetPositionFromMatrix4(playerWorldTransform_->matWorld_); }
	const Vector3 GetRadius() { return Vector3(3.0f, 3.0f, 3.0f); }
};

class Player :public Collider
{
private:
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
	PlayerAttack attack_;

	bool isHit = false; // falseのときに当たり判定が発生
	Timer hitTimer = 100;
	bool isDraw = true;
	Timer drawInterval = 5;
	int hp_ = 10;
	uint16_t LorR = 0;// 1 = 右向き,　0 = 左向き 
	float Rot = 0;
	bool walkFlag = true;
	float walkPos = 0.0f;
	void Move();
	bool Turn(float& pos1D, Direction nextDirection, float limitPos);
	Player() = default;
	~Player() = default;
	float DirectionToRadian();
	void WalkMotion();			//歩くモーション
public:
	enum { Root, Head, Chest, HandLeft, HandRight, FootLeft, FootRight };
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