#include "Skydome.h"

void Skydome::Initialize()
{
	worldTransform_.Initialize();
	worldTransform_.scale_ = { size, size, size };
	worldTransform_.Update();
	modelSkydome = Model::CreateFromOBJ("skydome", true);
}

void Skydome::Draw(ViewProjection viewProjection)
{
	modelSkydome->Draw(worldTransform_, viewProjection);
}