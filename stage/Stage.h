#pragma once
#include <vector>
#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "collider/CollisionManager.h"
#include "DebugCamera.h"
#include "BlockManager.h"
#include "particleManager/ParticleManager.h"

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
	//FbxModel* fbxModel_;
	//FbxObject3d* fbxObject_;
	//WorldTransform fbxObjWT;

public:
	~Stage();
	void Initialize();
	void Update();
	void Draw();
};