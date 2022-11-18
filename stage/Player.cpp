#include "Player.h"
#define PI 3.14159
std::unique_ptr<Player>  Player::GetInstance()
{
	static std::unique_ptr<Player> player = std::make_unique<Player>();
	return move(player);
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
	viewProjection_ = viewProjection;
}

void Player::Move()
{
	float horizontalSpd = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT))* 0.5f;

	// 移動
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

	// ジャンプ
	if (input_->PushKey(DIK_SPACE))
	{
		jamp_.StartJamp(1.5f, 0.1f, 2.0f);
	}
	jamp_.Update(worldTransform_[0].translation_.y);

	viewProjection_->eye = viewProjection_->target = worldTransform_[0].translation_ + Vector3(0, 5.0f, 0);

	// 方向転換
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
	modelKnight[1]->Draw(worldTransform_[1], *viewProjection_);	//頭
	modelKnight[2]->Draw(worldTransform_[2], *viewProjection_);	//胴
	modelKnight[3]->Draw(worldTransform_[3], *viewProjection_);	//左腕
	modelKnight[4]->Draw(worldTransform_[4], *viewProjection_);	//右腕
	modelKnight[5]->Draw(worldTransform_[5], *viewProjection_);	//左足
	modelKnight[6]->Draw(worldTransform_[6], *viewProjection_);	//右足
}

// 当たり判定の前に行う
void Player::UpdateSpeed()
{
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
	if(input_->PushKey(DIK_LEFT))//左右の判定
	{
		LorR = 0;
	}
	if(input_->PushKey(DIK_RIGHT))
	{
		LorR = 1;
	}

#pragma region 手前
	if (worldTransform_[0].translation_.z <= -24.5)//手前
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

		//胴
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//左腕
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z - 1.4f;

		//右腕
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z + 1.4f;

		//左足
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z - 0.6f;

		//右足
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z + 0.6f;
	}
#pragma endregion

#pragma region 奥
	else if (worldTransform_[0].translation_.z >= 24.5)//手前
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

		//胴
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//左腕
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z - 1.4f;

		//右腕
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z + 1.4f;

		//左足
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z - 0.6f;

		//右足
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z + 0.6f;
	}
#pragma endregion

#pragma region 左
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
	
		//頭
		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//胴
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//左腕
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x + 1.4f;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z;

		//右腕
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x - 1.4f;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z;

		//左足
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x + 0.6f;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z;

		//右足
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x - 0.6f;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z;
	}
#pragma endregion

#pragma region 右
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
		//頭
		worldTransform_[1].rotation_.y = Rot * PI / 180;
		worldTransform_[1].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[1].translation_.y = worldTransform_[0].translation_.y + 3.5f;
		worldTransform_[1].translation_.z = worldTransform_[0].translation_.z;

		//胴
		worldTransform_[2].rotation_.y = Rot * PI / 180;
		worldTransform_[2].translation_.x = worldTransform_[0].translation_.x;
		worldTransform_[2].translation_.y = worldTransform_[0].translation_.y + 1.0f;
		worldTransform_[2].translation_.z = worldTransform_[0].translation_.z;

		//左腕
		worldTransform_[3].rotation_.y = Rot * PI / 180;
		worldTransform_[3].translation_.x = worldTransform_[0].translation_.x + 1.4f;
		worldTransform_[3].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[3].translation_.z = worldTransform_[0].translation_.z;

		//右腕
		worldTransform_[4].rotation_.y = Rot * PI / 180;
		worldTransform_[4].translation_.x = worldTransform_[0].translation_.x - 1.4f;
		worldTransform_[4].translation_.y = worldTransform_[0].translation_.y + 0.8f;
		worldTransform_[4].translation_.z = worldTransform_[0].translation_.z;

		//左足
		worldTransform_[5].rotation_.y = Rot * PI / 180;
		worldTransform_[5].translation_.x = worldTransform_[0].translation_.x + 0.6f;
		worldTransform_[5].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[5].translation_.z = worldTransform_[0].translation_.z;

		//右足
		worldTransform_[6].rotation_.y = Rot * PI / 180;
		worldTransform_[6].translation_.x = worldTransform_[0].translation_.x - 0.6f;
		worldTransform_[6].translation_.y = worldTransform_[0].translation_.y - 0.3f;
		worldTransform_[6].translation_.z = worldTransform_[0].translation_.z;
	}
#pragma endregion
	
	//各worldTransformの更新
	worldTransform_[1].Update();
	worldTransform_[2].Update();
	worldTransform_[3].Update();
	worldTransform_[4].Update();
	worldTransform_[5].Update();
	worldTransform_[6].Update();
}

