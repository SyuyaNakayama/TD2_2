#pragma once
#include "Collider.h"
#include "stage/player/Player.h"
#include "stage/enemy/Enemy.h"

class CollisionManager
{
private:
	bool CheckBoxCollisionPair(Collider* colliderA, Collider* colliderB);
public:
	void CheckAllCollisions(Player* player, Enemy* enemy);
};