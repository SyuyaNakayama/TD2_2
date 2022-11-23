#pragma once
#include "Input.h"
#include "../stage/Jamp.h"
#include "Model.h"
#include "scene.h"
#include "timer/Timer.h"
#include "./stage/Shake.h"
#include "PlayerAttack.h"
#include "Sprite.h"

class Player :public Collider
{
private:
	std::vector<WorldTransform> worldTransform_;
	std::vector<Model*> modelKnight;
	ViewProjection* viewProjection_ = nullptr;
	Input* input_ = Input::GetInstance();
	uint32_t texture_ = 0;
	uint32_t textureHP_ = 0;
	Sprite* HpUI = nullptr;
	uint32_t textureHPback_ = 0;
	Sprite* HpBackUI = nullptr;
	const float CAMERA_DISTANCE = 30.0f;
	Direction direction_ = Front;
	bool isTurn_ = 0;
	const int LERP_FLAME = 60;
	int nowFlame = 0;
	Vector3 larpVec[2]{};
	Timer walkTimer_ = 10;
	PlayerAttack attack_;
	Shake shake_;

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
	void SpriteDraw();
	Direction GetDirection() { return direction_; }
	std::vector<WorldTransform> GetWorldTransforms() { return worldTransform_; }
	void SetWorldTransforms(std::vector<WorldTransform> worldTransforms) { worldTransform_ = worldTransforms; }
	void SetUIPosition();
	PlayerAttack* GetAttack() { return &attack_; }
	void SetIsDraw(bool isdraw) { isDraw = isdraw; }

	void OnCollision(Collider* collider);
	int GetPlayerHp() { return hp_; }
	const Vector3 GetWorldPosition() { return GetWorldTranslation(worldTransform_[1].matWorld_); }
	const Vector3 GetRadius() { return Vector3(2.0f, 3.0f, 3.0f); }
};