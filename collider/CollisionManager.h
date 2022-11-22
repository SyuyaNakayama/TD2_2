#pragma once
#include "Collider.h"
#include "stage/enemy/Enemy.h"

class CollisionManager
{
private:
	bool CheckBoxCollisionPair(Collider* colliderA, Collider* colliderB);
public:
	void CheckAllCollisions(Enemy* enemy);
};