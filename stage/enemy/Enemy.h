#pragma once
#include "collider/Collider.h"
#include "WorldTransform.h"
#include "Model.h"
#include "TextureManager.h"
#include "ViewProjection.h"
#include "Input.h"
#include "DebugText.h"
#include "Bless.h"

class Enemy :public Collider
{
private:
	const static uint16_t modelNum = 12;
	WorldTransform worldTransform_[modelNum] = {};
	Model* model_ = nullptr;
	Model* modelDoragon[modelNum] = {};
	uint32_t texture_ = 0;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	float Rot = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	bool isStandby = true;
	uint16_t timer = 30;
	float standbyRot = 0.0f;
	bool isUp = false;
	bool isBreath = false;
	bool isCharge = false;

	float origPosY[12] =	{ 0.0f,14.0f,14.0f,15.0f,14.0f,11.5f,8.0f,5.5f,2.2f,-2.0f,-7.0f, -12.5f };//元の座標
	float origPosZ[12] =	{ 0.0f,-4.0f,-4.0f, 2.0f, 4.5f, 6.0f,5.0f,4.0f,3.5f, 3.5f, 4.0f, 4.5f };
	float chargePosY[12] =	{ 0.0f,14.0f,14.0f,15.0f,14.0f,11.5f,8.0f,5.5f,2.2f,-2.0f,-7.0f, -12.5f };
	float chargePosZ[12] =	{ 0.0f,	5.0f, 5.0f, 9.5f,10.0f,10.0f, 9.0f,9.0f,9.0f,9.0f, 9.5f, 10.0f };
	void Move();
	// ブレス
	Bless breath_;
public:
	void Initialize();
	void Update();
	void Draw(ViewProjection viewProjection);

	void OnCollision(Collider* collider) {};
	const Vector3 GetWorldPosition() { return worldTransform_[0].translation_; }
	const Vector3 GetRadius() { return worldTransform_[0].scale_; }

	float ParPos(float x) { return x / 20.0f; }//親子関係にすると座標がおかしくなるため

	void ParentInitialize();	//親子関係の初期化

	void ParentUpdate();

	void StandbyMotion();		//待機のモーション

	void BreathMotion();		//ブレスのモーション

	void BiteMotion();			//嚙みつきのモーション

};