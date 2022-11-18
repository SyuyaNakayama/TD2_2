#include "Player.h"
using namespace MathUtility;

Player* Player::GetInstance()
{
	static Player* player = new Player;
	return player;
}

void Player::Initialize(ViewProjection* viewProjection)
{
	debugText_ = DebugText::GetInstance();
	model_ = Model::Create();
	input_ = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0,2.0f,-POLE_RAD };
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

	// ˆÚ“®
	switch (direction_)
	{
	case Front:	worldTransform_.translation_.x += horizontalSpd;	break;
	case Right:	worldTransform_.translation_.z += horizontalSpd;	break;
	case Back:	worldTransform_.translation_.x -= horizontalSpd;	break;
	case Left:	worldTransform_.translation_.z -= horizontalSpd;	break;
	}

	// ƒWƒƒƒ“ƒv
	if (input_->PushKey(DIK_SPACE))
	{
		jamp_.StartJamp(1.5f, 0.1f, 2.0f);
	}
	jamp_.Update(worldTransform_.translation_.y);

	viewProjection_->eye = viewProjection_->target = worldTransform_.translation_;
	viewProjection_->target.y += 2.0f;
	if (!isTurn_)
	{
		viewProjection_->eye += GetCameraPos(direction_, CAMERA_DISTANCE);
		larpVec[0] = viewProjection_->eye;

		// •ûŒü“]Š·
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
	worldTransform_.Update();
}

void Player::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

void Player::OnCollision(Collider* collider)
{

}