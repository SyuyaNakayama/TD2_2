#include "Block.h"

void Block::Initialize(Direction direction)
{
	model_ = Model::CreateFromOBJ("cloud", true);
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
	case Front:	translation = { pos.x - POLE_RAD,pos.y,-POLE_RAD };	break;
	case Right:	translation = { POLE_RAD,pos.y,pos.x - POLE_RAD };
			  Rot = 90 * PI / 180;
			  break;
		
	case Back:	translation = { -pos.x + POLE_RAD,pos.y,POLE_RAD };	break;
	case Left:	translation = { -POLE_RAD,pos.y,-pos.x + POLE_RAD };
			 Rot = 90 * PI / 180;
			 break;
	}
	w.rotation_.y = 90 * PI / 180;
	w.translation_ = translation;
	w.rotation_.y = Rot;
	w.scale_ = rad;
	w.Update();
	worldTransforms_.push_back(w);
}
