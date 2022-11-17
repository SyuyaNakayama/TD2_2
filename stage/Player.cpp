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
	worldTransform_.translation_ = { -POLE_RAD,2.0f,-POLE_RAD };
	viewProjection_ = viewProjection;
}

void Player::Move()
{
	float horizontalSpd = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT))* 0.5f;

	// 移動
	switch (direction_)
	{
	case Front:
		worldTransform_.translation_.x += horizontalSpd;
		break;
	case Right:
		worldTransform_.translation_.z += horizontalSpd;
		break;
	case Back:
		worldTransform_.translation_.x -= horizontalSpd;
		break;
	case Left:
		worldTransform_.translation_.z -= horizontalSpd;
		break;
	}

	// ジャンプ
	if (input_->PushKey(DIK_SPACE))
	{
		jamp_.StartJamp(1.5f, 0.1f, 2.0f);
	}
	jamp_.Update(worldTransform_.translation_.y);

	viewProjection_->eye = viewProjection_->target = worldTransform_.translation_ + Vector3(0, 5.0f, 0);

	// 方向転換
	switch (direction_)
	{
	case Front:
		viewProjection_->eye.z -= CAMERA_DISTANCE;
		Turn(worldTransform_.translation_.x, Left, -POLE_RAD);
		Turn(worldTransform_.translation_.x, Right, POLE_RAD);
		break;
	case Right:
		viewProjection_->eye.x += CAMERA_DISTANCE;
		Turn(worldTransform_.translation_.z, Front, -POLE_RAD);
		Turn(worldTransform_.translation_.z, Back, POLE_RAD);
		break;
	case Back:
		viewProjection_->eye.z += CAMERA_DISTANCE;
		Turn(worldTransform_.translation_.x, Left, -POLE_RAD);
		Turn(worldTransform_.translation_.x, Right, POLE_RAD);
		break;
	case Left:
		viewProjection_->eye.x -= CAMERA_DISTANCE;
		Turn(worldTransform_.translation_.z, Front, -POLE_RAD);
		Turn(worldTransform_.translation_.z, Back, POLE_RAD);
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
	worldTransform_.Update();
}

void Player::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_);
}

// 当たり判定の前に行う
void Player::UpdateSpeed()
{
}

void Player::OnCollision(Collider* collider)
{

}