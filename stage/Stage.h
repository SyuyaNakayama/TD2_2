#pragma once
#include <vector>
#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "collider/CollisionManager.h"
#include "DebugCamera.h"
#include "BlockManager.h"
#include "particleManager/ParticleManager.h"
#include "AxisIndicator.h"
#include "Shake.h"

class Stage
{
private:
	DebugText* debugText_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;
	ViewProjection viewProjection_;
	Model* model_ = nullptr;
	std::unique_ptr<Player> player_ = nullptr;
	CollisionManager collisionManager;
	Enemy enemy_;
	BlockManager blockManager_;
	ParticleManager particleManager_;
	AxisIndicator* axisIndicator_ = nullptr;
	Shake shake_;

public:
	~Stage();
	void Initialize();
	void Update();
	void Draw();
};