#pragma once
#include "Model.h"

class Skydome
{
public:
	void Initialize();
	void Draw(ViewProjection viewProjection);

private:
	WorldTransform worldTransform_;
	Model* modelSkydome = nullptr;
	float size = 100.0f;
};
