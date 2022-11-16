#include "Block.h"

void Block::Initialize(Direction direction)
{
	model_ = Model::Create();
	direction_ = direction;
}

void Block::Draw(ViewProjection viewProjection)
{
	for (const WorldTransform& w : worldTransforms_) { model_->Draw(w, viewProjection); }
}

void Block::Add(Vector2 pos, Vector3 rad)
{
	WorldTransform w;
	Vector3 translation{};
	w.Initialize();

	switch (direction_)
	{
	case Front:
		translation = { pos.x - POLE_RAD,pos.y,-POLE_RAD };
		break;
	case Right:
		break;
	case Back:
		break;
	case Left:
		break;
	}

	w.translation_ = translation;
	w.scale_ = rad;
	w.Update();
	worldTransforms_.push_back(w);
}
