#pragma once
#include <vector>
#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "collider/CollisionManager.h"
#include "DebugCamera.h"
#include "fbx/FbxObject3d.h"

class Stage
{
private:
	DebugText* debugText_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;
	ViewProjection viewProjection_;
	std::vector<WorldTransform> blocks_;
	Model* model_ = nullptr;
	std::unique_ptr<Player> player_ = nullptr;
	CollisionManager collisionManager;
	Enemy enemy_;
	//FbxModel* fbxModel_;
	//FbxObject3d* fbxObject_;
	//WorldTransform fbxObjWT;

public:
	~Stage();
	void Initialize();
	void Update();
	void Draw();
};