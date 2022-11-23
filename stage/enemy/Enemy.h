#pragma once
#include "collider/Collider.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"
#include "Bless.h"
#include "./stage/player/Player.h"

float DirectionToRadian(Direction direction);

class Enemy :public Collider
{
private:
	enum AttackPattern { Idle, Breath, Bite };

	const static uint16_t modelNum = 12;
	WorldTransform worldTransform_[modelNum] = {};
	Model* modelDoragon[modelNum] = {};
	uint32_t texture_ = 0;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	float Rot = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	bool isStandby = true;

	float standbyRot = 0.0f;
	bool isUp = false;

	bool isBreathMotion = false;
	bool isCharge = false;
	bool isBreath = false;
	bool isClose = false;
	bool isStop1 = false;
	bool isStop2 = false;
	uint16_t breathTimer = 30;

	bool isBiteMotion = false;
	bool isOpen = false;
	bool isStop3 = false;
	bool isBite = false;
	bool isStop4 = false;
	bool isOrig = false;
	uint16_t biteTimer = 30;

	int hp_ = 50;

	float origPosY[12] = { 0.0f,14.0f, 14.0f, 15.0f, 14.0f,11.5f, 8.0f, 5.5f, 2.2f,  -2.0f, -7.0f, -12.5f };//元の座標
	float origPosZ[12] = { 0.0f,-4.0f, -4.0f,  2.0f,  4.5f, 6.0f, 5.0f, 4.0f, 3.5f,   3.5f,  4.0f,  4.5f };
	float origRotX[12] = { 0.0f, 0.0f,  0.0f,-90.0f,-50.0f, 6.0f,43.0f,16.0f, 4.0f,  -4.0f, -4.0f, -5.0f };

	float chargePosY[12] = { 0.0f,16.5f, 16.5f, 13.5f, 10.5f, 7.5f, 4.5f, 1.4f,-2.2f,  -6.0f,-11.0f, -16.5f };//目指す座標
	float chargePosZ[12] = { 0.0f,	5.0f,  5.0f,  9.5f, 10.0f,10.0f, 9.0f, 9.0f, 9.0f,   9.0f,  9.5f,  10.0f };
	float chargeRotX[12] = { 0.0f,20.0f, 30.0f,-26.5f,  0.0f,11.0f, 9.0f, 0.0f, 4.0f,   4.0f, -4.0f,  5.0f };

	float breathPosY[12] = { 0.0f,14.0f, 14.0f, 15.0f, 14.0f,11.5f, 8.0f, 5.5f, 2.2f,  -2.0f, -7.0f, -12.5f };
	float breathPosZ[12] = { 0.0f,-4.0f, -4.0f,  2.0f,  4.5f, 6.0f, 5.0f, 4.0f, 3.5f,   3.5f,  4.0f,  4.5f };
	float breathRotX[12] = { 0.0f,25.0f,-20.0f,-90.0f,-50.0f, 6.0f,43.0f,16.0f, 4.0f,  -4.0f, -4.0f, -5.0f };

	float bitePosY[12] = { 0.0f,  3.8f,  3.8f,   8.0f,  8.5f,  8.0f,  6.0f,  3.2f, -0.5f,  -4.0f, -9.0f, -14.5f };
	float bitePosZ[12] = { 0.0f,-18.0f,-18.0f, -11.5f, -8.0f, -5.0f, -2.0f,  0.3f,  1.7f,   1.8f,  1.8f,  1.8f };
	float biteRotX[12] = { 0.0f,-17.0f,-17.0f,-103.0f,-85.5f,-66.7f,-49.5f,-33.5f, -8.0f,  -4.0f, -4.0f, -5.0f };

	float diffPosY[12] = {};
	float diffPosZ[12] = {};
	float diffRotX[12] = {};

	ViewProjection* viewProjection_ = nullptr;
	void Move();
	// ブレス
	Bless breath_;
	Player* player_ = Player::GetInstance();

	Timer attackInterval = 10;
	AttackPattern attackPattern = Idle;
	bool rotStop = false;
public:
	void Initialize(ViewProjection* viewProjection);
	void Update();
	void Draw();

	void OnCollision(Collider* collider);
	const Vector3 GetWorldPosition() { return GetWorldTranslation(worldTransform_[1].matWorld_) + Vector3(0, 0, -5.0f) * MathUtility::Matrix4RotationY((DirectionToRadian(player_->GetDirection()))); }
	const Vector3 GetRadius() { return Vector3(3.0f, 3.0f, 3.0f); }
	Bless* GetBreath() { return &breath_; }

	float ParPos(float x) { return x / 20.0f; }//親子関係にすると座標がおかしくなるため

	void ParentInitialize();	//親子関係の初期化

	void ParentUpdate();

	void StandbyMotion();		//待機のモーション

	void BreathMotion();		//ブレスのモーション

	void BiteMotion();			//嚙みつきのモーション
	
	static void(Enemy::* AttackFunc[])();
};