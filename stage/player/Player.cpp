#include "Player.h"

Player* Player::GetInstance()
{
	static Player* player = new Player;
	return player;
}

void Player::Initialize(Model* model1, Model* model2, Model* model3, Model* model4, Model* model5, Model* model6, 
	ViewProjection* viewProjection)
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	modelKnight[0] = Model::Create();
	modelKnight[1] = model1;
	modelKnight[2] = model2;
	modelKnight[3] = model3;
	modelKnight[4] = model4;
	modelKnight[5] = model5;
	modelKnight[6] = model6;
	input_ = Input::GetInstance();
	worldTransform_[0].Initialize();
	ParentInitialize();
	worldTransform_[0].translation_ = {-POLE_RAD,2.0f,-POLE_RAD};
	direction_ = Front;
	viewProjection_ = viewProjection;
}

void Player::Move()
{
	float horizontalSpd = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT))* 0.5f;

	// à⁄ìÆ
	switch (direction_)
	{
	case Front:
		worldTransform_[0].translation_.x += horizontalSpd;
		break;
	case Right:
		worldTransform_[0].translation_.z += horizontalSpd;
		break;
	case Back:
		worldTransform_[0].translation_.x -= horizontalSpd;
		break;
	case Left:
		worldTransform_[0].translation_.z -= horizontalSpd;
		break;
	}

	// ÉWÉÉÉìÉv
	if (input_->PushKey(DIK_SPACE))
	{
		jamp_.StartJamp(1.5f, 0.1f, 2.0f);
	}
	jamp_.Update(worldTransform_[0].translation_.y);

	viewProjection_->eye = viewProjection_->target = worldTransform_[0].translation_ + Vector3(0, 5.0f, 0);

	// ï˚å¸ì]ä∑
	switch (direction_)
	{
	case Front:
		viewProjection_->eye.z -= CAMERA_DISTANCE;
		Turn(worldTransform_[0].translation_.x, Left, -POLE_RAD);
		Turn(worldTransform_[0].translation_.x, Right, POLE_RAD);
		break;
	case Right:
		viewProjection_->eye.x += CAMERA_DISTANCE;
		Turn(worldTransform_[0].translation_.z, Front, -POLE_RAD);
		Turn(worldTransform_[0].translation_.z, Back, POLE_RAD);
		break;
	case Back:
		viewProjection_->eye.z += CAMERA_DISTANCE;
		Turn(worldTransform_[0].translation_.x, Left, -POLE_RAD);
		Turn(worldTransform_[0].translation_.x, Right, POLE_RAD);
		break;
	case Left:
		viewProjection_->eye.x -= CAMERA_DISTANCE;
		Turn(worldTransform_[0].translation_.z, Front, -POLE_RAD);
		Turn(worldTransform_[0].translation_.z, Back, POLE_RAD);
		break;
	}
}

void Player::Turn(float& pos1D, Direction nextDirection, float limitPos)
{
	bool isTurn;
	if (limitPos <= 0) { isTurn = pos1D < limitPos; }
	else { isTurn = pos1D > limitPos; }
	if (!isTurn) { return; }
	pos1D = limitPos;
	direction_ = nextDirection;
}

void Player::Update()
{
	Move();
	ParentUpdate();
	worldTransform_[0].Update();
}

void Player::Draw()
{
	//modelKnight[0]->Draw(worldTransform_[0], *viewProjection_);
	modelKnight[1]->Draw(worldTransform_[1], *viewProjection_);	//ì™
	modelKnight[2]->Draw(worldTransform_[2], *viewProjection_);	//ì∑
	modelKnight[3]->Draw(worldTransform_[3], *viewProjection_);	//ç∂òr
	modelKnight[4]->Draw(worldTransform_[4], *viewProjection_);	//âEòr
	modelKnight[5]->Draw(worldTransform_[5], *viewProjection_);	//ç∂ë´
	modelKnight[6]->Draw(worldTransform_[6], *viewProjection_);	//âEë´
}

void Player::OnCollision(Collider* collider)
{

}

void Player::ParentInitialize()
{
	worldTransform_[1].Initialize();
	worldTransform_[2].Initialize();
	worldTransform_[3].Initialize();
	worldTransform_[4].Initialize();
	worldTransform_[5].Initialize();
	worldTransform_[6].Initialize();
}

void Player::ParentUpdate()
{
	ParentSetPosition();
}

void Player::ParentSetPosition()
{
	if(input_->PushKey(DIK_LEFT))//ç∂âEÇÃîªíË
	{
		LorR = 0;
	}
	if(input_->PushKey(DIK_RIGHT))
	{
		LorR = 1;
	}

#pragma region éËëO
	if (worldTransform_[0].translation_.z <= -24.5)//éËëO
	{
		if(LorR == 0)
		{
			Rot = 90;
		}
		else
		{
			Rot = 270;
		}

		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//ì∑
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//ç∂òr
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z - 1.4f;

		//âEòr
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z + 1.4f;

		//ç∂ë´
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z - 0.6f;

		//âEë´
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z + 0.6f;
	}
#pragma endregion

#pragma region âú
	else if (worldTransform_[0].translation_.z >= 24.5)//éËëO
	{
		if (LorR == 1)
		{
			Rot = 90;
		}
		else
		{
			Rot = 270;
		}
		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//ì∑
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//ç∂òr
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z - 1.4f;

		//âEòr
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z + 1.4f;

		//ç∂ë´
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z - 0.6f;

		//âEë´
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z + 0.6f;
	}
#pragma endregion

#pragma region ç∂
	else if (worldTransform_[0].translation_.x <= -24.5f)
	{
		if (LorR == 1)
		{
			Rot = 0;
		}
		else
		{
			Rot = 180;
		}
	
		//ì™
		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//ì∑
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//ç∂òr
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x + 1.4f;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z;

		//âEòr
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x - 1.4f;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z;

		//ç∂ë´
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x + 0.6f;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z;

		//âEë´
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x - 0.6f;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z;
	}
#pragma endregion

#pragma region âE
	else if (worldTransform_[0].translation_.x >= 24.5f)
	{
		if (LorR == 0)
		{
			Rot = 0;
		}
		else
		{
			Rot = 180;
		}
		//ì™
		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//ì∑
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//ç∂òr
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x + 1.4f;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z;

		//âEòr
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x - 1.4f;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z;

		//ç∂ë´
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x + 0.6f;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z;

		//âEë´
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x - 0.6f;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z;
	}
#pragma endregion
	
	//äeworldTransformÇÃçXêV
	worldTransform_[1].Update();
	worldTransform_[2].Update();
	worldTransform_[3].Update();
	worldTransform_[4].Update();
	worldTransform_[5].Update();
	worldTransform_[6].Update();
}

