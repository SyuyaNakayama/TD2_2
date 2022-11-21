#pragma once
#include <vector>
#include "collider/CollisionManager.h"
#include "DebugCamera.h"
#include "block/BlockManager.h"
#include "particleManager/ParticleManager.h"
#include "Shake.h"
#include "Skydome.h"

class Stage
{
private:
	DebugText* debugText_ = DebugText::GetInstance();
	DebugCamera* debugCamera_ = nullptr;
	ViewProjection viewProjection_;
	Player* player_ = Player::GetInstance();
	CollisionManager collisionManager;
	Enemy enemy_;
	BlockManager blockManager_;
	ParticleManager particleManager_;
	Shake shake_;
	Skydome* skydome = new Skydome();
	float size = 1.0f;
	
public:
	~Stage();
	void Initialize();
	void Update();
	void Draw();
	void SetEye(Vector3 eye) { viewProjection_.eye = eye; viewProjection_.UpdateMatrix(); }
	void SetTarget(Vector3 target) { viewProjection_.target = target; viewProjection_.UpdateMatrix(); }
};