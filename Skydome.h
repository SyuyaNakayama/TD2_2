#pragma once
#include "TextureManager.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"

class Skydome
{
public:
	void Initialize();
	void Update();
	void Draw(ViewProjection viewProjection);

private:
	WorldTransform worldTransform_;
	Model* modelSkydome = nullptr;
	float size = 1.0f;
};
