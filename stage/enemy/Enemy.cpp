#include "Enemy.h"

void Enemy::Move()
{
}

void Enemy::Initialize(ViewProjection* viewProjection)
{
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	modelDoragon[0] = Model::CreateFromOBJ("Doragon", true);
	modelDoragon[1] = Model::CreateFromOBJ("Doragon_Head", true);	//頭
	modelDoragon[2] = Model::CreateFromOBJ("Doragon_Jaw", true);	//顎
	//首
	for (int i = 3; i < modelNum; i++)
	{
		modelDoragon[i] = Model::CreateFromOBJ("Doragon_neck", true);
	}
	ParentInitialize();
	worldTransform_[0].scale_ = {20.0f,20.0f,20.0f};
	// ブレスの初期化
	viewProjection_ = viewProjection;
	breath_.Initialize(worldTransform_[0].translation_,{0,0,-0.5f}, viewProjection_);
}

void Enemy::Update()
{
	worldTransform_[0].Update();
	ParentUpdate();
	breath_.Update();
}

void Enemy::Draw()
{
	// 各パーツ(頭、顎、首)
	for (int i = 1; i < modelNum; i++)
	{
		modelDoragon[i]->Draw(worldTransform_[i], *viewProjection_);
	}
	breath_.Draw();
}

void Enemy::ParentInitialize()
{
	worldTransform_[0].Initialize();

	//頭
	worldTransform_[1].translation_ = { 0.0f,ParPos(14.0f),ParPos(-4.0f) };

	//顎
	worldTransform_[2].translation_ = { 0.0f,ParPos(14.0f),ParPos(-4.0f) };

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
	if (input_->PushKey(DIK_1))//ブレスモーション
	{
		isCharge = true;
		isBreathMotion = true;
	}
	if (input_->PushKey(DIK_2))//噛みつきモーション
	{
		isOpen = true;
		isBiteMotion = true;
	}
	if(isBiteMotion ==false && isBreathMotion == false)
	{
		StandbyMotion();
	}

	BreathMotion();
	BiteMotion();
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
			//isBreath = true;
			isStop1 = true;
			isCharge = false;
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
			isBreath = false;
			//isClose = true;
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
		for (int i = 1; i < 12; i++)//
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
		}
	}
}

void Enemy::BiteMotion()
{
	//口開く
	if(isOpen == true)
	{
		for (int i = 1; i < 12; i++)//座標をセット
		{
			diffPosY[i] = breathPosY[i] - origPosY[i];
			diffPosZ[i] = breathPosZ[i] - origPosZ[i];
			diffRotX[i] = breathRotX[i] - origRotX[i];
		}
		biteTimer--;
		for (int i = 1; i < 12; i++)//
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
		}
	}
}