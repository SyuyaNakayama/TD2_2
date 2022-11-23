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
	bool isAttacked = false;
	Vector3 hitOffset_{};

public:
	void Initialize(WorldTransform* playerWorldTransform);
	void Motion(Vector3 hitOffset);	//攻撃のモーション
	bool IsAttack() { return isAttack; }
	bool IsAttacked() { return isAttacked; }
	void SetIsAttacked(bool isAttacked_) { isAttacked = isAttacked_; }
	void OnCollision(Collider* collider) {}
	const Vector3 GetWorldPosition() { return GetWorldTranslation(playerWorldTransform_->matWorld_) + hitOffset_; }
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
	PlayerAttack* GetAttack() { return &attack_; }

	void OnCollision(Collider* collider);
	const Vector3 GetWorldPosition() { return GetWorldTranslation(worldTransform_[1].matWorld_); }
	const Vector3 GetRadius() { return Vector3(2.0f, 3.0f, 3.0f); }
};