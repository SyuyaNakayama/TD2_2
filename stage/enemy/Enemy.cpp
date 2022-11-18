#include "Enemy.h"

void Enemy::Move()
{
}

void Enemy::Initialize()
{
	model_ = Model::CreateFromOBJ("DragonHead", true);
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 20.0f,20.0f,20.0f };
}

void Enemy::Update()
{
	worldTransform_.Update();
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
