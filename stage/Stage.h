#pragma once
#include <vector>
#include "collider/CollisionManager.h"
#include "block/BlockManager.h"
#include "Skydome.h"
#include "player/Player.h"

class Stage
{
private:
	ViewProjection viewProjection_;
	Player* player_ = Player::GetInstance();
	CollisionManager collisionManager;
	Enemy* enemy_ = Enemy::GetInstance();
	BlockManager blockManager_;
	Skydome* skydome = new Skydome();

public:
	~Stage();
	void Initialize();
	void Update();
	void Draw();
	void SpriteDraw();
	void SetEye(Vector3 eye) { viewProjection_.eye = eye; viewProjection_.UpdateMatrix(); }
	void SetTarget(Vector3 target) { viewProjection_.target = target; viewProjection_.UpdateMatrix(); }
};