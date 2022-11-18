#pragma once
#include <vector>
#include "player/Player.h"
#include "enemy/Enemy.h"
#include "collider/CollisionManager.h"
#include "DebugCamera.h"
#include "block/BlockManager.h"
#include "particleManager/ParticleManager.h"
#include "Shake.h"

class Stage
{
private:
	DebugText* debugText_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;
	ViewProjection viewProjection_;
	Player* player_ = nullptr;
	Model* model_ = nullptr;
	Model* PLHead = nullptr;
	Model* PLbody = nullptr;
	Model* PLhandLeft = nullptr;
	Model* PLhandRight = nullptr;
	Model* PLfootLeft = nullptr;
	Model* PLfootRight = nullptr;

	CollisionManager collisionManager;
	Enemy enemy_;
	BlockManager blockManager_;
	ParticleManager particleManager_;
	Model* DragonHead = nullptr;
	Shake shake_;

public:
	~Stage();
	void Initialize();
	void Update();
	void Draw();
};