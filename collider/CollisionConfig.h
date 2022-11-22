#pragma once

struct CollisionAttribute
{
	enum
	{
		Player = 0b1,
		PlayerAttack = 0b1 << 1,
		Enemy = 0b1 << 2,
		EnemyBreath = 0b1 << 3,
	};
};

struct CollisionMask
{
	enum
	{
		Player = ~(CollisionAttribute::Player | CollisionAttribute::PlayerAttack),
		Enemy = ~(CollisionAttribute::Enemy | CollisionAttribute::EnemyBreath)
	};
};