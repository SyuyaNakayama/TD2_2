#include "Player.h"
using namespace MathUtility;

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

Vector3 GetCameraPos(Direction direction, float cameraDistance)
{
	float angle = 0;

	switch (direction)
	{
	case Right:	angle = 3.0f * PI / 2.0f;	break;
	case Back:	angle = -PI;				break;
	case Left:	angle = PI / 2.0f;			break;
	}

	return Vector3(0, 0, -cameraDistance) * Matrix4RotationY(angle);
}

void Player::Move()
{
	float horizontalSpd = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT)) * 0.5f;
	Vector3 larpVec[2]{};

	// Ú®
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

	// Wv
	if (input_->PushKey(DIK_SPACE))
	{
		jamp_.StartJamp(1.5f, 0.1f, 2.0f);
	}
	jamp_.Update(worldTransform_[0].translation_.y);

	viewProjection_->eye = viewProjection_->target = worldTransform_.translation_;
	viewProjection_->target.y += 2.0f;
	if (!isTurn_)
	{
		viewProjection_->eye += GetCameraPos(direction_, CAMERA_DISTANCE);
		larpVec[0] = viewProjection_->eye;

		// ûü]·
		switch (direction_)
		{
		case Front:
			Turn(worldTransform_.translation_.x, Left, -POLE_RAD);
			Turn(worldTransform_.translation_.x, Right, POLE_RAD);
			break;
		case Right:
			Turn(worldTransform_.translation_.z, Front, -POLE_RAD);
			Turn(worldTransform_.translation_.z, Back, POLE_RAD);
			break;
		case Back:
			Turn(worldTransform_.translation_.x, Left, -POLE_RAD);
			Turn(worldTransform_.translation_.x, Right, POLE_RAD);
			break;
		case Left:
			Turn(worldTransform_.translation_.z, Front, -POLE_RAD);
			Turn(worldTransform_.translation_.z, Back, POLE_RAD);
			break;
		}
	}

	if (isTurn_)
	{
		larpVec[1] = viewProjection_->eye + GetCameraPos(direction_, CAMERA_DISTANCE);
		float t = (float)++nowFlame / (float)LERP_FLAME;
		viewProjection_->eye = lerp(larpVec[0], larpVec[1], t);
		
		if (nowFlame >= LERP_FLAME) 
		{
			nowFlame = 0;
			isTurn_ = 0; 
		}
	}
}

void Player::Turn(float& pos1D, Direction nextDirection, float limitPos)
{
	if (limitPos <= 0) { isTurn_ = pos1D < limitPos; }
	else { isTurn_ = pos1D > limitPos; }
	if (!isTurn_) { return; }
	pos1D = limitPos;
	nowFlame = 0;
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
	modelKnight[1]->Draw(worldTransform_[1], *viewProjection_);	//ª
	modelKnight[2]->Draw(worldTransform_[2], *viewProjection_);	//·
	modelKnight[3]->Draw(worldTransform_[3], *viewProjection_);	//¶r
	modelKnight[4]->Draw(worldTransform_[4], *viewProjection_);	//Er
	modelKnight[5]->Draw(worldTransform_[5], *viewProjection_);	//¶«
	modelKnight[6]->Draw(worldTransform_[6], *viewProjection_);	//E«
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
	if(input_->PushKey(DIK_LEFT))//¶EÌ»è
	{
		LorR = 0;
	}
	if(input_->PushKey(DIK_RIGHT))
	{
		LorR = 1;
	}

#pragma region èO
	if (worldTransform_[0].translation_.z <= -24.5)//èO
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

		//·
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//¶r
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z - 1.4f;

		//Er
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z + 1.4f;

		//¶«
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z - 0.6f;

		//E«
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z + 0.6f;
	}
#pragma endregion

#pragma region 
	else if (worldTransform_[0].translation_.z >= 24.5)//èO
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

		//·
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//¶r
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z - 1.4f;

		//Er
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z + 1.4f;

		//¶«
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z - 0.6f;

		//E«
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z + 0.6f;
	}
#pragma endregion

#pragma region ¶
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
	
		//ª
		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//·
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//¶r
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x + 1.4f;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z;

		//Er
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x - 1.4f;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z;

		//¶«
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x + 0.6f;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z;

		//E«
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x - 0.6f;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z;
	}
#pragma endregion

#pragma region E
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
		//ª
		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//·
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//¶r
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x + 1.4f;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z;

		//Er
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x - 1.4f;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z;

		//¶«
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x + 0.6f;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z;

		//E«
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x - 0.6f;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z;
	}
#pragma endregion
	
	//eworldTransformÌXV
	worldTransform_[1].Update();
	worldTransform_[2].Update();
	worldTransform_[3].Update();
	worldTransform_[4].Update();
	worldTransform_[5].Update();
	worldTransform_[6].Update();
}

