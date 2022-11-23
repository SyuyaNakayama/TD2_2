#include "PlayerAttack.h"
#include "Input.h"
#include "./stage/enemy/Enemy.h"
#include "SoundManager.h"

void PlayerAttack::Initialize(WorldTransform* playerWorldTransform)
{
	playerWorldTransform_ = playerWorldTransform;
	SetCollisionAttribute(CollisionAttribute::PlayerAttack);
	SetCollisionMask(CollisionMask::Player);
}

void PlayerAttack::Motion(Vector3 hitOffset)
{
	hitOffset_ = hitOffset;
	if (!isAttack)
	{
		if (Input::GetInstance()->TriggerKey(DIK_SPACE) && Enemy::GetInstance()->GetEnemyHp() > 0)
		{
			isAttack = isUp = true; isAttacked = false;
			SoundManager::GetInstance()->PlaySE(SoundManager::P_Attack);
		}
		else { return; }
	}

	if (isUp)// �U��グ��
	{
		ATrot += 20.0f;
		// �^��܂ŉE����グ����
		isUp = ATrot < 180;
	}
	if (!isUp) // �U�艺����
	{
		ATrot -= 30.0f;
		isAttack = ATrot > 0.0f;
		isAttacked = true;
	}

	playerWorldTransform_->rotation_.x = ATrot * PI / 180.0f;
}