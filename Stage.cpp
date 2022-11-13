#include "Stage.h"
using namespace std;

void Stage::Initialize(ViewProjection& viewProjection)
{
	viewProjection_ = viewProjection;
	model_ = Model::Create();
	blocks_.resize(50);
	for (size_t i = 0; i < blocks_.size(); i++)
	{
		blocks_[i].Initialize();
		blocks_[i].translation_ = { -POLE_RAD + 2.0f * (float)i,(float)i * 2.0f,-POLE_RAD };
		blocks_[i].Update();
	}
	player_ = Player::GetInstance();
	player_->Initialize(viewProjection);
}

void Stage::Update()
{
	player_->UpdateSpeed();
	player_->Update();
	player_->DirectionChange(POLE_RAD);
}

void Stage::Draw()
{
	player_->Draw();
	for (WorldTransform& block : blocks_) { model_->Draw(block, viewProjection_); }
}
