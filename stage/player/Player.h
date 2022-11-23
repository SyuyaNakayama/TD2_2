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
	uint32_t textureHP_ = 0;
	Sprite* HpUI = nullptr;
	uint32_t textureHPback_ = 0;
	Sprite* HpBackUI = nullptr;
	const float CAMERA_DISTANCE = 30.0f;
	Direction direction_ = Front;
	Jamp jamp_;
	bool isTurn_ = 0;
	const int LERP_FLAME = 60;
	int nowFlame = 0;
	Vector3 larpVec[2]{};
	Timer walkTimer_ = 10;

	int hp_ = 20;
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
	void SpriteDraw();
	Direction GetDirection() { return direction_; }
	std::vector<WorldTransform> GetWorldTransforms() { return worldTransform_; }
	void SetWorldTransforms(std::vector<WorldTransform> worldTransforms) { worldTransform_ = worldTransforms; }
	void SetUIPosition();

	void OnCollision(Collider* collider);
	const Vector3 GetWorldPosition() { return worldTransform_[0].translation_; }
	const Vector3 GetRadius() { return worldTransform_[0].scale_; }
};