#include "Skydome.h"

void Skydome::Initialize()
{
	worldTransform_.Initialize();
	size = 100.0f;
	worldTransform_.scale_ = Vector3(size, size, size);
	worldTransform_.Update();
	modelSkydome = Model::CreateFromOBJ("skydome",true);
}

void Skydome ::Update ()
{

}

void Skydome::Draw(ViewProjection viewProjection)
{
	modelSkydome->Draw(worldTransform_, viewProjection);
}