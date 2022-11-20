#include "Player.h"
using namespace MathUtility;

std::vector<std::string> modelName =
{
	"head","chest","handLeft","handRight","footLeft","footRight"
};

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

float Player::DirectionToRadian()
{
	switch (direction_)
	{
	case Front:
		if (LorR == 0) { return PI / 2.0f; }
		else { return 3.0f * PI / 2.0f; }
	case Right:
		if (LorR == 0) { return 0; }
		else { return PI; }
	case Back:
		if (LorR == 1) { return PI / 2.0f; }
		else { return 3.0f * PI / 2.0f; }
	case Left:
		if (LorR == 1) { return 0; }
		else { return PI; }
	}
	return 0;
}

Player* Player::GetInstance()
{
	static Player* player = new Player;
	return player;
}

void Player::Initialize(ViewProjection* viewProjection)
{
	debugText_ = DebugText::GetInstance();
	worldTransform_.resize(7);
	modelKnight.resize(worldTransform_.size() - 1);
	input_ = Input::GetInstance();
	direction_ = Front;
	viewProjection_ = viewProjection;

	for (size_t i = 0; i < modelKnight.size(); i++)
	{
		modelKnight[i] = Model::CreateFromOBJ("Knight_" + modelName[i], true);
	}
	for (WorldTransform& w : worldTransform_) { w.Initialize(); }
	worldTransform_[Root].translation_ = { -POLE_RAD,2.0f,-POLE_RAD };
	// êeéqä÷åWÇåãÇ‘
	for (size_t i = 1; i < worldTransform_.size(); i++)
	{
		worldTransform_[i].parent_ = &worldTransform_[0];
	}
	worldTransform_[Chest].translation_.y += 1.0f;
	worldTransform_[Head].translation_.y += 3.5f;
	worldTransform_[HandLeft].translation_.y += 1.7f;
	worldTransform_[HandLeft].translation_.x += 1.4f;
	worldTransform_[HandRight].translation_.y += 1.7f;
	worldTransform_[HandRight].translation_.x -= 1.4f;
	worldTransform_[FootLeft].translation_.y -= 0.3f;
	worldTransform_[FootLeft].translation_.x -= 0.6f;
	worldTransform_[FootRight].translation_.y -= 0.3f;
	worldTransform_[FootRight].translation_.x += 0.6f;
}

void Player::Move()
{
	float horizontalSpd = (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT)) * 0.5f;

	// à⁄ìÆ
	switch (direction_)
	{
	case Front:
		worldTransform_[Root].translation_.x += horizontalSpd;
		break;
	case Right:
		worldTransform_[Root].translation_.z += horizontalSpd;
		break;
	case Back:
		worldTransform_[Root].translation_.x -= horizontalSpd;
		break;
	case Left:
		worldTransform_[Root].translation_.z -= horizontalSpd;
		break;
	}

	// ÉWÉÉÉìÉv
	if (input_->PushKey(DIK_SPACE))
	{
		jamp_.StartJamp(1.5f, 0.1f, 2.0f);
	}
	jamp_.Update(worldTransform_[0].translation_.y);

	viewProjection_->eye = viewProjection_->target = worldTransform_[0].translation_;
	viewProjection_->target.y += 2.0f;
	if (!isTurn_)
	{
		viewProjection_->eye += GetCameraPos(direction_, CAMERA_DISTANCE);
		larpVec[0] = viewProjection_->eye;

		// ï˚å¸ì]ä∑
		switch (direction_)
		{
		case Front:
			if (Turn(worldTransform_[Root].translation_.x, Left, -POLE_RAD)) { break; }
			Turn(worldTransform_[Root].translation_.x, Right, POLE_RAD);
			break;
		case Right:
			if (Turn(worldTransform_[Root].translation_.z, Front, -POLE_RAD)) { break; };
			Turn(worldTransform_[Root].translation_.z, Back, POLE_RAD);
			break;
		case Back:
			if (Turn(worldTransform_[Root].translation_.x, Left, -POLE_RAD)) { break; };
			Turn(worldTransform_[Root].translation_.x, Right, POLE_RAD);
			break;
		case Left:
			if (Turn(worldTransform_[Root].translation_.z, Front, -POLE_RAD)) { break; };
			Turn(worldTransform_[Root].translation_.z, Back, POLE_RAD);
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

bool Player::Turn(float& pos1D, Direction nextDirection, float limitPos)
{
	if (limitPos <= 0) { isTurn_ = pos1D < limitPos; }
	else { isTurn_ = pos1D > limitPos; }
	if (!isTurn_) { return false; }
	pos1D = limitPos;
	nowFlame = 0;
	direction_ = nextDirection;
	return true;
}

void Player::Update()
{
	Move();
	// ç∂âEÇÃîªíË
	if (input_->PushKey(DIK_LEFT)) { LorR = 0; }
	if (input_->PushKey(DIK_RIGHT)) { LorR = 1; }
	worldTransform_[Root].rotation_.y = DirectionToRadian();
	AttackMotion();
	WalkMotion();
	for (WorldTransform& w : worldTransform_) { w.Update(); }
}

void Player::Draw()
{
	for (size_t i = 0; i < modelKnight.size(); i++)
	{
		modelKnight[i]->Draw(worldTransform_[i + 1], *viewProjection_);
	}
}

void Player::OnCollision(Collider* collider)
{

}

void Player::WalkMotion()
{
	int walkTIME = 10;
	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_RIGHT))
	{
		walkTimer++;
		if (walkFlag == true)
		{
			walkPos += 0.1f;
			if (walkTimer >= walkTIME)
			{
				walkTimer = 1;
				walkFlag = false;
			}
		}
		if (walkFlag == false)
		{
			walkPos -= 0.1f;
			if (walkTimer >= walkTIME)
			{
				walkTimer = 0;
				walkFlag = true;
			}
		}
	}
	else // Ç±ÇÃÇ‹Ç‹ÇæÇ∆é~Ç‹Ç¡ÇΩéûÇ…éËë´ÇÃà íuÇ™Ç∏ÇÍÇƒÇ¢ÇÈÇÃÇ≈íºÇ∑
	{
		walkPos = 0.0f;
	}

	if (!isAttack)// çUåÇÉÇÅ[ÉVÉáÉìÇ∆èdÇ»Ç¡ÇƒÇµÇ‹Ç§ÇΩÇﬂ
	{
		worldTransform_[HandLeft].rotation_.x = walkPos * PI / 18;
		worldTransform_[HandRight].rotation_.x = walkPos * PI / 18;
	}

	// ÉÇÅ[ÉVÉáÉìÇîΩâf
	worldTransform_[FootLeft].translation_.z = walkPos;
	worldTransform_[FootRight].translation_.z = -walkPos;
}

void Player::AttackMotion()
{
	if (!isAttack)
	{
		if (input_->TriggerKey(DIK_A)) { isAttack = isUp = true; }
		else { return; }
	}

	if (isUp)// êUÇËè„Ç∞ÇÈ
	{
		ATrot += 20.0f;
		// ê^è„Ç‹Ç≈âEéËÇè„Ç∞ÇΩÇÁ
		isUp = ATrot < 180;
	}
	if (!isUp) // êUÇËâ∫Ç∞ÇÈ
	{
		ATrot -= 30.0f;
		isAttack = ATrot > 0.0f;
	}

	worldTransform_[HandRight].rotation_.x = ATrot * PI / 180.0f;
}