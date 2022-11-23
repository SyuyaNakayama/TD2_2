#include "Player.h"
#include "./stage/enemy/Enemy.h"
#include "SoundManager.h"
#include "SafeDelete.h"
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
	worldTransform_.resize(7);
	modelKnight.resize(worldTransform_.size() - 1);
	input_ = Input::GetInstance();
	direction_ = Front;
	viewProjection_ = viewProjection;
	SetCollisionAttribute(CollisionAttribute::Player);
	SetCollisionMask(CollisionMask::Player);
	hp_ = 10;
	attack_.Initialize(&worldTransform_[HandRight]);
	isHit = false;
	isDraw = true;

	for (size_t i = 0; i < modelKnight.size(); i++)
	{
		modelKnight[i] = Model::CreateFromOBJ("Knight_" + modelName[i], true);
	}
	for (WorldTransform& w : worldTransform_) { w.Initialize(); }
	worldTransform_[Root].translation_ = { 0,2.0f,-POLE_RAD };
	// 親子関係を結ぶ
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

	// 移動
	if (hp_ > 0&& Enemy::GetInstance()->GetEnemyHp() > 0)
	{
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
	}

	viewProjection_->eye = viewProjection_->target = worldTransform_[0].translation_;
	viewProjection_->target.y += 2.0f;
	if (!isTurn_)
	{
		viewProjection_->eye += GetCameraPos(direction_, CAMERA_DISTANCE);
		larpVec[0] = viewProjection_->eye;

		// 方向転換
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
	// 左右の判定
	if (hp_ > 0 && Enemy::GetInstance()->GetEnemyHp() > 0)
	{
		if (input_->PushKey(DIK_LEFT)) { LorR = 0; }
		if (input_->PushKey(DIK_RIGHT)) { LorR = 1; }
	}
	worldTransform_[Root].rotation_.y = DirectionToRadian();
	Vector3 hitOffset = Vector3(0, 0, -3.0f) * Matrix4RotationY(DirectionToRadian());
	if (hp_ > 0)
	{
		attack_.Motion(hitOffset);
		if (Enemy::GetInstance()->GetEnemyHp() > 0) { WalkMotion(); }
	}
	SetUIPosition();
	for (WorldTransform& w : worldTransform_) { w.Update(); }

	if (isHit)
	{
		if (drawInterval.CountDown()) { isDraw = !isDraw; }
		if (hitTimer.CountDown())
		{
			isHit = false;
			isDraw = true;
		};
	}

	shake_.Update(*viewProjection_);
}

void Player::Draw()
{
	if (!isDraw) { return; }
	for (size_t i = 0; i < modelKnight.size(); i++)
	{
		modelKnight[i]->Draw(worldTransform_[i + 1], *viewProjection_);
	}
}

void Player::SetUIPosition()
{
	HpBackUI->SetPosition({ 1280 / 2 - 65.0f, worldTransform_[Root].translation_.y + 230.0f });
	HpUI->SetPosition({ 1280 / 2 - 65.0f, worldTransform_[Root].translation_.y + 230.0f });
}

void Player::SpriteDraw()
{
	HpBackUI->SetSize({ 10.0f * 16.0f,15.0f });
	HpBackUI->Draw();
	HpUI->SetSize({ hp_ * 16.0f,15.0f });
	HpUI->Draw();
}

void Player::OnCollision(Collider* collider)
{
	if (isHit || hp_ <= 0 || Enemy::GetInstance()->GetEnemyHp() <= 0) { return; }
	hp_--;
	isHit = true;
	shake_.ShakeStart(5.0f);
	SoundManager::GetInstance()->PlaySE(SoundManager::P_Damage);
}

void Player::Finalize()
{
	SafeDelete(HpUI);
	SafeDelete(HpBackUI);
	for (size_t i = 0; i < modelKnight.size(); i++)
	{
		SafeDelete(modelKnight[i]);
	}
	modelKnight.clear();
	delete this;
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
	else // このままだと止まった時に手足の位置がずれているので直す
	{
		walkPos = 0.0f;
		walkTimer_.Reset();
	}

	if (!attack_.IsAttack())// 攻撃モーションと重なってしまうため
	{
		worldTransform_[HandLeft].rotation_.x = walkPos * PI / 18;
		worldTransform_[HandRight].rotation_.x = walkPos * PI / 18;
	}

	// モーションを反映
	worldTransform_[FootLeft].translation_.z = walkPos;
	worldTransform_[FootRight].translation_.z = -walkPos;
}