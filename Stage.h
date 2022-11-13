#pragma once
#include <vector>
#include "Model.h"
#include "player/Player.h"
#include "enemy/Enemy.h"
#include "collider/CollisionManager.h"
#include "DebugCamera.h"
#include "FbxObject3d.h"

class Stage
{
private:
	DebugText* debugText_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;
	ViewProjection viewProjection_;
	std::vector<WorldTransform> blocks_;
	Model* model_ = nullptr;
	const float POLE_RAD = 25.0f;
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