#pragma once
#include <list>
#include "Collider.h"
#include <memory>
#include "stage/Player.h"
#include "stage/Enemy.h"

class CollisionManager
{
private:
	bool CheckBoxCollisionPair(Collider* colliderA, Collider* colliderB);
public:
	void CheckAllCollisions(Player* player, Enemy* enemy);
};