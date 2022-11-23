#pragma once
#include "collider/Collider.h"
#include "WorldTransform.h"

class PlayerAttack :public Collider
{
private:
	WorldTransform* playerWorldTransform_ = nullptr;
	bool isUp = false;
	float ATrot = 0.0f;
	bool isAttack = false;
	bool isAttacked = false;
	Vector3 hitOffset_{};

public:
	void Initialize(WorldTransform* playerWorldTransform);
	void Motion(Vector3 hitOffset);	//UŒ‚‚Ìƒ‚[ƒVƒ‡ƒ“
	bool IsAttack() { return isAttack; }
	bool IsAttacked() { return isAttacked; }
	void SetIsAttacked(bool isAttacked_) { isAttacked = isAttacked_; }
	void OnCollision(Collider* collider) {}
	const Vector3 GetWorldPosition() { return GetWorldTranslation(playerWorldTransform_->matWorld_) + hitOffset_; }
	const Vector3 GetRadius() { return Vector3(3.0f, 3.0f, 3.0f); }
};