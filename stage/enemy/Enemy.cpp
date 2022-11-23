#include "Enemy.h"

void(Enemy::* Enemy::AttackFunc[])() =
{
	&Enemy::StandbyMotion,&Enemy::BreathMotion,&Enemy::BiteMotion
};

float DirectionToRadian(Direction direction)
{
	float angle = 0;

	switch (direction)
	{
	case Right:	angle = 3.0f * PI / 2.0f;	break;
	case Back:	angle = -PI;				break;
	case Left:	angle = PI / 2.0f;			break;
	}
	return angle;
}

void Enemy::Move()
{
	if (attackPattern == 2 && !rotStop) { worldTransform_[0].rotation_.y = DirectionToRadian(player_->GetDirection()); rotStop = true; }
	if (attackPattern != 0) { return; }
	rotStop = false;
	Vector3 direction = player_->GetWorldPosition() - GetWorldPosition();
	worldTransform_[0].rotation_.y = atan2f(direction.x, direction.z) + PI;
}

Enemy* Enemy::GetInstance()
{
	static Enemy* enemy = new Enemy;
	return enemy;
}

void Enemy::Initialize(ViewProjection* viewProjection)
{
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	SetCollisionAttribute(CollisionAttribute::Enemy);
	SetCollisionMask(CollisionMask::Enemy);
	hp_ = 50;
	isDamage = 0;
	attackPattern = Idle;
	isBiteMotion = false;
	isOpen = false;
	isStop3 = false;
	isBite = false;
	isStop4 = false;
	isOrig = false;
	biteTimer = 30;

	for (size_t i = 0; i < 12; i++)
	{
		diffPosY[i] = {};
		diffPosZ[i] = {};
		diffRotX[i] = {};
	}

	modelDoragon[0] = Model::CreateFromOBJ("Doragon", true);
	modelDoragon[1] = Model::CreateFromOBJ("Doragon_Head", true);	//頭
	modelDoragon[2] = Model::CreateFromOBJ("Doragon_Jaw", true);	//顎
	textureHP_ = TextureManager::Load("green.png");
	HpUI = Sprite::Create(textureHP_, { 150.0f,5.0f });
	textureHPback_ = TextureManager::Load("gray.png");
	HpBackUI = Sprite::Create(textureHPback_, { 150.0f,5.0f });
	//首
	for (int i = 3; i < modelNum; i++)
	{
		modelDoragon[i] = Model::CreateFromOBJ("Doragon_neck", true);
	}
	ParentInitialize();
	worldTransform_[0].scale_ = { 20.0f,20.0f,20.0f };
	// ブレスの初期化
	viewProjection_ = viewProjection;
}

void Enemy::Update()
{
	Move();
	worldTransform_[0].Update();
	ParentUpdate();
	breath_.Update();
	isDamage = false;

	debugText_->SetPos(0, 0);
	debugText_->Printf("%d", hp_);
}

void Enemy::Draw()
{
	// 各パーツ(頭、顎、首)
	for (int i = 1; i < modelNum; i++)
	{
		if (!isDamage) { modelDoragon[i]->Draw(worldTransform_[i], *viewProjection_); }
		else { modelDoragon[i]->Draw(worldTransform_[i], *viewProjection_, TextureManager::Load("white1x1.png")); }
	}
	breath_.Draw();
}

void Enemy::SpriteDraw()
{
	HpBackUI->SetSize({ 50 * 20.0f,25.0f });
	HpBackUI->Draw();
	HpUI->SetSize({ hp_ * 20.0f,25.0f });
	HpUI->Draw();
}

void Enemy::ParentInitialize()
{
	worldTransform_[0].Initialize();

	//頭
	worldTransform_[1].translation_ = { 0.0f,ParPos(14.0f),ParPos(-4.0f) };
	worldTransform_[1].rotation_.x = 0;

	//顎
	worldTransform_[2].translation_ = { 0.0f,ParPos(14.0f),ParPos(-4.0f) };
	worldTransform_[2].rotation_.x = 0;

	//首
	worldTransform_[3].translation_ = { 0.0f,ParPos(15.0f),ParPos(2.0f) };
	worldTransform_[3].rotation_.x = -90 * PI / 180;

	worldTransform_[4].translation_ = { 0.0f,ParPos(14.0f),ParPos(4.5f) };
	worldTransform_[4].rotation_.x = -50 * PI / 180;

	worldTransform_[5].translation_ = { 0.0f,ParPos(11.5f),ParPos(6.0f) };
	worldTransform_[5].rotation_.x = 6 * PI / 180;

	worldTransform_[6].translation_ = { 0.0f,ParPos(8.0f),ParPos(5.0f) };
	worldTransform_[6].rotation_.x = 43 * PI / 180;

	worldTransform_[7].scale_ = Vector3(1.15f, 1.15f, 1.15f);
	worldTransform_[7].translation_ = { 0.0f,ParPos(5.5f),ParPos(4.0f) };
	worldTransform_[7].rotation_.x = 16 * PI / 180;

	worldTransform_[8].scale_ = Vector3(1.3f, 1.3f, 1.3f);
	worldTransform_[8].translation_ = { 0.0f,ParPos(2.2f),ParPos(3.5f) };
	worldTransform_[8].rotation_.x = 4 * PI / 180;

	worldTransform_[9].scale_ = Vector3(1.55f, 1.55f, 1.55f);
	worldTransform_[9].translation_ = { 0.0f,ParPos(-2.0f),ParPos(3.5f) };
	worldTransform_[9].rotation_.x = -4 * PI / 180;

	worldTransform_[10].scale_ = Vector3(1.85f, 1.85f, 1.86f);
	worldTransform_[10].translation_ = { 0.0f,ParPos(-7.0f),ParPos(4.0f) };
	worldTransform_[10].rotation_.x = -4 * PI / 180;

	worldTransform_[11].scale_ = Vector3(2.1f, 2.1f, 2.1f);
	worldTransform_[11].translation_ = { 0.0f,ParPos(-12.5f),ParPos(4.5f) };
	worldTransform_[11].rotation_.x = -5 * PI / 180;

	for (size_t i = 1; i < modelNum; i++)
	{
		worldTransform_[i].parent_ = &worldTransform_[0];
		worldTransform_[i].Initialize();
	}
}

void Enemy::ParentUpdate()
{
	switch (attackPattern)
	{
	case Enemy::Idle:
		if (attackInterval.CountDown())
		{
			int pattern = 0;//rand() % 2;
			if (pattern == 0) { attackPattern = Enemy::Breath; }
			else { attackPattern = Enemy::Bite; }
			attackInterval = rand() % 120 + 30;
		}
		break;
	case Enemy::Breath:
		if (!isBreathMotion)//ブレスモーション
		{
			isCharge = true;
			isBreathMotion = true;
		}
		break;
	case Enemy::Bite:
		if (!isBiteMotion)//噛みつきモーション
		{
			isOpen = true;
			isBiteMotion = true;
		}
		break;
	}

	(this->*AttackFunc[attackPattern])();

	for (int i = 0; i < modelNum; i++)
	{
		worldTransform_[i].Update();
	}
}

void Enemy::StandbyMotion()
{
	if (isStandby == true)
	{
		if (isUp == true)
		{
			standbyRot += 0.1f;

			if (standbyRot >= 0.0f)
			{
				isUp = false;
			}
		}
		if (isUp == false)
		{
			standbyRot -= 0.1f;

			if (standbyRot <= -10.0f)
			{
				isUp = true;
			}
		}
	}
	worldTransform_[1].rotation_.x = standbyRot * PI / 180;
}

void Enemy::BreathMotion()
{
	static Vector3 direction{};
	//溜めるモーション
	if (isCharge == true)
	{
		for (int i = 1; i < 12; i++)//座標をセット
		{
			diffPosY[i] = chargePosY[i] - origPosY[i];
			diffPosZ[i] = chargePosZ[i] - origPosZ[i];
			diffRotX[i] = chargeRotX[i] - origRotX[i];
		}

		breathTimer--;
		for (int i = 1; i < 12; i++)//
		{
			worldTransform_[i].translation_.y += ParPos(diffPosY[i] / 30);
			worldTransform_[i].translation_.z += ParPos(diffPosZ[i] / 30);
			worldTransform_[i].rotation_.x += (diffRotX[i] / 30) * PI / 180;
		}

		if (breathTimer <= 0.0f)
		{
			breathTimer = 20;//ここは20
			isStop1 = true;
			isCharge = false;
			direction = player_->GetWorldPosition() - GetWorldPosition();
			direction.normalize();
		}

	}

	//数秒待機
	if (isStop1 == true)
	{
		breathTimer--;

		if (breathTimer <= 0.0f)
		{
			breathTimer = 20;//ここは20
			isBreath = true;
			isStop1 = false;
		}
	}

	//ブレスを吐くモーション
	if (isBreath == true)
	{
		for (int i = 1; i < 12; i++)//座標をセット
		{
			diffPosY[i] = breathPosY[i] - chargePosY[i];
			diffPosZ[i] = breathPosZ[i] - chargePosZ[i];
			diffRotX[i] = breathRotX[i] - chargeRotX[i];
		}

		breathTimer--;
		for (int i = 1; i < 12; i++)//
		{
			worldTransform_[i].translation_.y += ParPos(diffPosY[i] / 20);
			worldTransform_[i].translation_.z += ParPos(diffPosZ[i] / 20);
			worldTransform_[i].rotation_.x += (diffRotX[i] / 20) * PI / 180;
		}
		if (breathTimer <= 0.0f)
		{
			breathTimer = 20;//ここは20
			breath_.Initialize(GetWorldTranslation(worldTransform_[1].matWorld_), direction, viewProjection_);
			isBreath = false;
			isStop2 = true;
		}
	}

	//数秒待機
	if (isStop2 == true)
	{
		breathTimer--;

		if (breathTimer <= 0.0f)
		{
			breathTimer = 20;//ここは20
			isClose = true;
			isStop2 = false;
		}
	}

	//口閉じる
	if (isClose == true)
	{
		for (int i = 1; i < 12; i++)//座標をセット
		{
			diffPosY[i] = origPosY[i] - breathPosY[i];
			diffPosZ[i] = origPosZ[i] - breathPosZ[i];
			diffRotX[i] = origRotX[i] - breathRotX[i];
		}

		breathTimer--;
		for (int i = 1; i < 12; i++)
		{
			worldTransform_[i].translation_.y += ParPos(diffPosY[i] / 20);
			worldTransform_[i].translation_.z += ParPos(diffPosZ[i] / 20);
			worldTransform_[i].rotation_.x += (diffRotX[i] / 20) * PI / 180;
		}
		if (breathTimer <= 0.0f)
		{
			breathTimer = 30;//ここは30
			isClose = false;
			isBreathMotion = false;
			attackPattern = Idle;
		}
	}
}

void Enemy::BiteMotion()
{
	//口開く
	if (isOpen == true)
	{
		for (int i = 1; i < 12; i++)//座標をセット
		{
			diffPosY[i] = breathPosY[i] - origPosY[i];
			diffPosZ[i] = breathPosZ[i] - origPosZ[i];
			diffRotX[i] = breathRotX[i] - origRotX[i];
		}
		biteTimer--;
		for (int i = 1; i < 12; i++)
		{
			worldTransform_[i].translation_.y += ParPos(diffPosY[i] / 30);
			worldTransform_[i].translation_.z += ParPos(diffPosZ[i] / 30);
			worldTransform_[i].rotation_.x += (diffRotX[i] / 30) * PI / 180;
		}
		if (biteTimer <= 0.0f)
		{
			biteTimer = 30;//ここは30
			isOpen = false;
			isStop3 = true;
		}
	}

	//数秒待機
	if (isStop3 == true)
	{
		biteTimer--;

		if (biteTimer <= 0.0f)
		{
			biteTimer = 20;//ここは20
			isBite = true;
			isStop3 = false;
		}
	}

	//噛むモーション
	if (isBite == true)
	{
		for (int i = 1; i < 12; i++)//座標をセット
		{
			diffPosY[i] = bitePosY[i] - breathPosY[i];
			diffPosZ[i] = bitePosZ[i] - breathPosZ[i];
			diffRotX[i] = biteRotX[i] - breathRotX[i];
		}
		biteTimer--;
		for (int i = 1; i < 12; i++)//
		{
			worldTransform_[i].translation_.y += ParPos(diffPosY[i] / 20);
			worldTransform_[i].translation_.z += ParPos(diffPosZ[i] / 20);
			worldTransform_[i].rotation_.x += (diffRotX[i] / 20) * PI / 180;
		}
		if (biteTimer <= 0.0f)
		{
			biteTimer = 200;//ここは200
			isBite = false;
			isStop4 = true;
		}
	}

	//数秒待機
	if (isStop4 == true)
	{
		biteTimer--;

		if (biteTimer <= 0.0f)
		{
			biteTimer = 40;//ここは40
			isOrig = true;
			isStop4 = false;
		}
	}

	//元の位置に戻る
	if (isOrig == true)
	{
		for (int i = 1; i < 12; i++)//座標をセット
		{
			diffPosY[i] = origPosY[i] - bitePosY[i];
			diffPosZ[i] = origPosZ[i] - bitePosZ[i];
			diffRotX[i] = origRotX[i] - biteRotX[i];
		}
		biteTimer--;
		for (int i = 1; i < 12; i++)//
		{
			worldTransform_[i].translation_.y += ParPos(diffPosY[i] / 40);
			worldTransform_[i].translation_.z += ParPos(diffPosZ[i] / 40);
			worldTransform_[i].rotation_.x += (diffRotX[i] / 40) * PI / 180;
		}
		if (biteTimer <= 0.0f)
		{
			biteTimer = 30;//ここは30
			isOrig = false;
			isBiteMotion = false;
			attackPattern = Idle;
		}
	}
}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->GetCollisionAttribute() != CollisionAttribute::PlayerAttack) { return; }
	if (!player_->GetAttack()->IsAttack()) { return; }
	if (player_->GetAttack()->IsAttacked()) { return; }
	hp_--;
	player_->GetAttack()->SetIsAttacked(true);
	isDamage = true;
}