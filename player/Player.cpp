#include "Player.h"

std::unique_ptr<Player>  Player::GetInstance()
{
	static std::unique_ptr<Player> player = std::make_unique<Player>();
	return move(player);
}

void Player::Initialize(ViewProjection* viewProjection, float poleRad)
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	input_ = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_ = { -25.0f,0,-25.0f };
	viewProjection_ = viewProjection;
	poleRadius_ = poleRad;
}

void Player::Move()
{
	worldTransform_.translation_ += spd_;
	viewProjection_->eye = viewProjection_->target = worldTransform_.translation_;
	switch (direction_)
	{
	case Player::Front:
		viewProjection_->eye.z -= CAMERA_DISTANCE;
		if (worldTransform_.translation_.x <= -poleRadius_)
		{
			viewProjection_->eye.x = viewProjection_->target.x =
				worldTransform_.translation_.x = -poleRadius_;
		}
		break;
	case Player::Right:
		viewProjection_->eye.x += CAMERA_DISTANCE;
		if (worldTransform_.translation_.z <= -poleRadius_)
		{
			viewProjection_->eye.z = viewProjection_->target.z =
				worldTransform_.translation_.z = -poleRadius_;
		}
		break;
	case Player::Back:
		break;
	case Player::Left:
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

void Player::UpdateSpeed()
{
	float horizontalSpd = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT));
	float verticalSpd = (input_->PushKey(DIK_UP) - input_->PushKey(DIK_DOWN));

	switch (direction_)
	{
	case Player::Front:
		spd_ = { horizontalSpd ,verticalSpd ,0 };
		break;
	case Player::Right:
		spd_ = { 0,verticalSpd ,horizontalSpd };
		break;
	case Player::Back:
		break;
	case Player::Left:
		break;
	}
	spd_.normalize();
	spd_ *= 0.2f;
}

void Player::DirectionChange()
{
	switch (direction_)
	{
	case Player::Front:
		if (worldTransform_.translation_.x >= poleRadius_)
		{
			worldTransform_.translation_.x = poleRadius_;
			direction_ = Right;
		}
		break;
	case Player::Right:
		break;
	case Player::Back:
		break;
	case Player::Left:
		break;
	}
	debugText_->SetPos(0, 0);
	debugText_->Printf("%f", worldTransform_.translation_.x);
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