#include "Enemy.h"

void Enemy::Move()
{
}

void Enemy::Initialize()
{
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	//modelDoragon[0] = Model::Create();
	modelDoragon[0] = Model::CreateFromOBJ("Doragon", true);
	modelDoragon[1] = Model::CreateFromOBJ("Doragon_Head", true);	//頭
	modelDoragon[2] = Model::CreateFromOBJ("Doragon_Jaw", true);	//顎
	//首
	for (int i = 3; i < modelNum; i++)
	{
		modelDoragon[i] = Model::CreateFromOBJ("Doragon_neck", true);
	}
	//worldTransform_[0].Initialize();
	ParentInitialize();
	worldTransform_[0].scale_ = {20.0f,20.0f,20.0f};
	// ブレスの初期化
	//breath_.Initialize(worldTransform_[0].translation_,{0,0,-0.5f},);
}

void Enemy::Update()
{
	worldTransform_[0].Update();
	ParentUpdate();
}

void Enemy::Draw(ViewProjection viewProjection)
{
	//modelDoragon[0]->Draw(worldTransform_[0], viewProjection);//大元

	// 各パーツ(頭、顎、首)
	for (int i = 1; i < modelNum; i++)
	{
		modelDoragon[i]->Draw(worldTransform_[i], viewProjection);
	}
}

void Enemy::ParentInitialize()
{
	worldTransform_[0].Initialize();

	//頭
	//worldTransform_[1].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	//worldTransform_[1].translation_ = { 0.0f,14.0f,-4.0f }; 
	worldTransform_[1].translation_ = { 0.0f,ParPos(14.0f),ParPos(-4.0f) };
	worldTransform_[1].parent_ = &worldTransform_[0];
	worldTransform_[1].Initialize();

	//顎
	//worldTransform_[2].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[2].translation_ = { 0.0f,ParPos(14.0f),ParPos(-4.0f) };
	worldTransform_[2].parent_ = &worldTransform_[0];
	worldTransform_[2].Initialize();

	//首
	//worldTransform_[3].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[3].translation_ = { 0.0f,ParPos(15.0f),ParPos(2.0f) };
	worldTransform_[3].rotation_.x = -90 * PI / 180;
	worldTransform_[3].parent_ = &worldTransform_[0];
	worldTransform_[3].Initialize();

	//worldTransform_[4].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[4].translation_ = { 0.0f,ParPos(14.0f),ParPos(4.5f) };
	worldTransform_[4].rotation_.x = -50 * PI / 180;
	worldTransform_[4].parent_ = &worldTransform_[0];
	worldTransform_[4].Initialize();

	//worldTransform_[5].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[5].translation_ = { 0.0f,ParPos(11.5f),ParPos(6.0f) };
	worldTransform_[5].rotation_.x = 6 * PI / 180;
	worldTransform_[5].parent_ = &worldTransform_[0];
	worldTransform_[5].Initialize();

	//worldTransform_[6].scale_ = Vector3(20.0f, 20.0f, 20.0f);
	worldTransform_[6].translation_ = { 0.0f,ParPos(8.0f),ParPos(5.0f) }; 
	worldTransform_[6].rotation_.x = 43 * PI / 180;
	worldTransform_[6].parent_ = &worldTransform_[0];
	worldTransform_[6].Initialize();

	worldTransform_[7].scale_ = Vector3(1.15f, 1.15f, 1.15f);
	worldTransform_[7].translation_ = { 0.0f,ParPos(5.5f),ParPos(4.0f) };
	worldTransform_[7].rotation_.x = 16 * PI / 180;
	worldTransform_[7].parent_ = &worldTransform_[0];
	worldTransform_[7].Initialize();

	worldTransform_[8].scale_ = Vector3(1.3f, 1.3f, 1.3f);
	worldTransform_[8].translation_ = { 0.0f,ParPos(2.2f),ParPos(3.5f) };
	worldTransform_[8].rotation_.x = 4 * PI / 180;
	worldTransform_[8].parent_ = &worldTransform_[0];
	worldTransform_[8].Initialize();

	worldTransform_[9].scale_ = Vector3(1.55f, 1.55f, 1.55f);
	worldTransform_[9].translation_ = { 0.0f,ParPos(-2.0f),ParPos(3.5f) };
	worldTransform_[9].rotation_.x = -4 * PI / 180;
	worldTransform_[9].parent_ = &worldTransform_[0];
	worldTransform_[9].Initialize();

	worldTransform_[10].scale_ = Vector3(1.85f, 1.85f, 1.86f);
	worldTransform_[10].translation_ = { 0.0f,ParPos(-7.0f),ParPos(4.0f) }; 
	worldTransform_[10].rotation_.x = -4 * PI / 180;
	worldTransform_[10].parent_ = &worldTransform_[0];
	worldTransform_[10].Initialize();

	worldTransform_[11].scale_ = Vector3(2.1f, 2.1f, 2.1f);
	worldTransform_[11].translation_ = { 0.0f,ParPos(-12.5f),ParPos(4.5f) };
	worldTransform_[11].rotation_.x = -5 * PI / 180;
	worldTransform_[11].parent_ = &worldTransform_[0];
	worldTransform_[11].Initialize();
}

void Enemy::ParentUpdate()
{
	//StandbyMotion();

	if(input_->PushKey(DIK_1))
	{
		isCharge = true;
	}
	BreathMotion();
	for (int i = 0; i < modelNum; i++)
	{
		worldTransform_[i].Update();
	}
}

void Enemy::StandbyMotion()
{
	if(isStandby == true)
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
	
	for (int i = 1; i < 3; i++)//頭、顎
	{
		worldTransform_[i].rotation_.x = standbyRot * PI / 180;
	}
}

void Enemy::BreathMotion()
{
	if (input_->PushKey(DIK_W)) {
		y += 0.1f;
	}
	if (input_->PushKey(DIK_S)) {
		y -= 0.1f;
	}
	if (input_->PushKey(DIK_A)) {
		z += 0.1f;
	}
	if (input_->PushKey(DIK_D)) {
		z -= 0.1;
	}
	if (input_->PushKey(DIK_R)) {
		Rot += 0.1;
	}
	if (input_->PushKey(DIK_F)) {
		Rot -= 0.1;
	}
	
	
	//if(isBreath == true)
	//{
	//	//isCharge = true;
	//	
	//}
	
	//溜めるモーション
	if (isCharge == true)
	{
		for (int i = 1; i < 12; i++)//座標をセット
		{
			diffPosY[i] = chargePosY[i] - origPosY[i];
			diffPosZ[i] = chargePosZ[i] - origPosZ[i];
			diffRotX[i] = chargeRotX[i] - origRotX[i];
		}

		timer--;
		for (int i = 1; i < 12; i++)//
		{
			worldTransform_[i].translation_.y += ParPos(diffPosY[i] / 30);
			worldTransform_[i].translation_.z += ParPos(diffPosZ[i] / 30);
			worldTransform_[i].rotation_.x += (diffRotX[i] / 30) * PI / 180;
		}

		if (timer <= 0.0f)
		{
			timer = 20;//ここは20
			isBreath = true;
			isCharge = false;
		}
	}

	//数秒待機

	//ブレスを吐くモーション
	if (isBreath == true)
	{
		for (int i = 1; i < 12; i++)//座標をセット
		{
			diffPosY[i] = breathPosY[i] - chargePosY[i];
			diffPosZ[i] = breathPosZ[i] - chargePosZ[i];
			diffRotX[i] = breathPosX[i] - chargeRotX[i];
		}

		timer--;
		for (int i = 1; i < 12; i++)//
		{
			worldTransform_[i].translation_.y += ParPos(diffPosY[i] / 20);
			worldTransform_[i].translation_.z += ParPos(diffPosZ[i] / 20);
			worldTransform_[i].rotation_.x += (diffRotX[i] / 20) * PI / 180;
		}
		if (timer <= 0.0f)
		{
			timer = 30;//ここは30
			isBreath = false;
		}
	}

	//数秒待機

	debugText_->SetPos(0, 0);
	debugText_->Printf("isCha:%d, timer:%f", isCharge,timer);
	debugText_->SetPos(0, 20);
	debugText_->Printf("Rot:%f", Rot);
}

void Enemy::BiteMotion()
{

}



