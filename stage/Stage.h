#pragma once
#include <vector>
#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "collider/CollisionManager.h"
#include "DebugCamera.h"
#include "fbx/FbxObject3d.h"
#include "BlockManager.h"

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
	FbxModel* fbxModel_;
	FbxObject3d* fbxObject_;
	WorldTransform fbxObjWT;

public:
	~Stage();
	void Initialize();
	void Update();
	void Draw();
	FbxObject3d* GetFbxObject() { return fbxObject_; }
};