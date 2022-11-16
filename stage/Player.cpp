#include "Player.h"

std::unique_ptr<Player>  Player::GetInstance()
{
	static std::unique_ptr<Player> player = std::make_unique<Player>();
	return move(player);
}

void Player::Initialize(ViewProjection* viewProjection)
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	input_ = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_ = { -POLE_RAD,0.0f,-POLE_RAD };
	viewProjection_ = viewProjection;
}

void Player::Move()
{
	worldTransform_.translation_ += spd_;
	viewProjection_->eye = viewProjection_->target = worldTransform_.translation_;
	switch (direction_)
	{
	case Front:
		viewProjection_->eye.z -= CAMERA_DISTANCE;
		// ç∂Ç…âùÇØÇ»Ç¢
		if (worldTransform_.translation_.x <= -POLE_RAD)
		{
			viewProjection_->eye.x = viewProjection_->target.x =
				worldTransform_.translation_.x = -POLE_RAD;
		}
		// ï˚å¸ì]ä∑
		if (worldTransform_.translation_.x >= POLE_RAD)
		{
			worldTransform_.translation_.x = POLE_RAD;
			direction_ = Right;
		}
		break;
	case Right:
		viewProjection_->eye.x += CAMERA_DISTANCE;
		if (worldTransform_.translation_.z <= -POLE_RAD)
		{
			viewProjection_->eye.z = viewProjection_->target.z =
				worldTransform_.translation_.z = -POLE_RAD;
		}
		if (worldTransform_.translation_.z >= POLE_RAD)
		{
			worldTransform_.translation_.z = POLE_RAD;
			direction_ = Back;
		}
		break;
	case Back:
		viewProjection_->eye.z += CAMERA_DISTANCE;
		if (worldTransform_.translation_.x >= POLE_RAD)
		{
			viewProjection_->eye.x = viewProjection_->target.x =
				worldTransform_.translation_.x = POLE_RAD;
		}
		if (worldTransform_.translation_.x <= -POLE_RAD)
		{
			worldTransform_.translation_.x = -POLE_RAD;
			direction_ = Left;
		}
		break;
	case Left:
		viewProjection_->eye.x -= CAMERA_DISTANCE;
		if (worldTransform_.translation_.z >= POLE_RAD)
		{
			viewProjection_->eye.z = viewProjection_->target.z =
				worldTransform_.translation_.z = POLE_RAD;
		}
		if (worldTransform_.translation_.z <= -POLE_RAD)
		{
			worldTransform_.translation_.z = -POLE_RAD;
			direction_ = Front;
		}
		break;
	}
}

void Player::Update()
{
	Move();
	worldTransform_.Update();
}

void Player::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

// ìñÇΩÇËîªíËÇÃëOÇ…çsÇ§
void Player::UpdateSpeed()
{
	float horizontalSpd = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT));
	float verticalSpd = (input_->PushKey(DIK_UP) - input_->PushKey(DIK_DOWN));

	switch (direction_)
	{
	case Front:
		spd_ = { horizontalSpd ,verticalSpd ,0 };
		break;
	case Right:
		spd_ = { 0,verticalSpd ,horizontalSpd };
		break;
	case Back:
		spd_ = { -horizontalSpd ,verticalSpd ,0 };
		break;
	case Left:
		spd_ = { 0,verticalSpd ,-horizontalSpd };
		break;
	}
	spd_.normalize();
	spd_ *= 0.5f;
}

void Player::OnCollision(Collider* collider)
{
	Vector3 vec = GetWorldPosition() - collider->GetWorldPosition();
	Vector3 cmpVec[2] =
	{
		collider->GetWorldPosition() - collider->GetRadius(),
		GetWorldPosition() + GetRadius() - spd_
	};
	Vector3 cmpVec2[2] =
	{
		collider->GetWorldPosition() + collider->GetRadius(),
		GetWorldPosition() - GetRadius() - spd_
	};
	if (vec.x <= 0)
	{
		if (cmpVec[0].x >= cmpVec[1].x)
		{
			spd_.x = 0;
		}
		else
		{
			spd_.z = 0;
		}
	}
	else
	{
		if (cmpVec2[0].x <= cmpVec2[1].x) { spd_.x = 0; }
		else { spd_.z = 0; }
	}
}