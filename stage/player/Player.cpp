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
	float rad[4][2] =
	{
		{PI / 2.0f,3.0f * PI / 2.0f},
		{0,PI},
		{3.0f * PI / 2.0f,PI / 2.0f},
		{PI,0},
	};

	return rad[direction_][LorR];
}

Player* Player::GetInstance()
{
	static Player* player = new Player;
	return player;
}

void Player::Initialize(ViewProjection* viewProjection)
{
	textureHP_ = TextureManager::Load("green.png");
	HpUI = Sprite::Create(textureHP_, { 150.0f,50.0f });
	textureHPback_ = TextureManager::Load("gray.png");
	HpBackUI = Sprite::Create(textureHPback_, { 150.0f,50.0f });
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
	worldTransform_[Root].translation_ = { 0,2.0f,-POLE_RAD };
	// êeéqä÷åWÇåãÇ‘
	for (size_t i = 1; i < worldTransform_.size(); i++)
	{
		worldTransform_[i].parent_ = &worldTransform_[0];
	}
	worldTransform_[Chest].translation_.y = 1.0f;
	worldTransform_[Head].translation_.y = 3.5f;
	worldTransform_[Head].rotation_.x = 0;
	worldTransform_[HandLeft].translation_ = { 1.4f,1.7f,0 };
	worldTransform_[HandRight].translation_ = { -1.4f,1.7f,0 };
	worldTransform_[FootLeft].translation_ = { -0.6f,-0.3f,0 };
	worldTransform_[FootRight].translation_ = { 0.6f,-0.3f,0 };
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
	if (input_->PushKey(DIK_UP))
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
	SetUIPosition();
	for (WorldTransform& w : worldTransform_) { w.Update(); }
}

void Player::Draw()
{
	for (size_t i = 0; i < modelKnight.size(); i++)
	{
		modelKnight[i]->Draw(worldTransform_[i + 1], *viewProjection_);
	}
}

void Player::SetUIPosition()
{
	HpBackUI->SetPosition({ 1280/2 - 65.0f, worldTransform_[Root].translation_.y + 230.0f});	
	HpUI->SetPosition({ 1280 / 2 - 65.0f, worldTransform_[Root].translation_.y + 230.0f });
}

void Player::SpriteDraw()
{
	HpBackUI->SetSize({ 20.0f*8.0f,15.0f });
	HpBackUI->Draw();
	HpUI->SetSize({ hp_* 8.0f,15.0f });
	HpUI->Draw();
}

void Player::OnCollision(Collider* collider)
{

}

void Player::WalkMotion()
{
	if (input_->PushKey(DIK_LEFT) || input_->PushKey(DIK_RIGHT))
	{
		if (walkFlag)
		{
			walkPos += 0.05f;
			if (walkTimer_.CountDown()) { walkFlag = false; }
		}
		if (!walkFlag)
		{
			walkPos -= 0.05f;
			if (walkTimer_.CountDown()) { walkFlag = true; }
		}
	}
	else // Ç±ÇÃÇ‹Ç‹ÇæÇ∆é~Ç‹Ç¡ÇΩéûÇ…éËë´ÇÃà íuÇ™Ç∏ÇÍÇƒÇ¢ÇÈÇÃÇ≈íºÇ∑
	{
		walkPos = 0.0f;
		walkTimer_.Reset();
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
		if (input_->TriggerKey(DIK_SPACE)) { isAttack = isUp = true; }
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