#pragma once

struct CollisionAttribute
{
	enum Enum
	{
		Player = 0b1,
		PlayerAttack = 0b1 << 1,
		Enemy = 0b1 << 2,
		EnemyBreath = 0b1 << 3,
	};
};

struct CollisionMask
{
	enum Enum
	{
		Player = ~(CollisionAttribute::Player | CollisionAttribute::PlayerAttack),
		Enemy = ~(CollisionAttribute::Enemy | CollisionAttribute::EnemyBreath),
		EnemyBreath = ~(CollisionAttribute::Enemy | CollisionAttribute::EnemyBreath | CollisionAttribute::PlayerAttack)
	};
};