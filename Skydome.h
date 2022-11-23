#pragma once
#include "Model.h"

class Skydome
{
public:
	void Initialize();
	void Draw(ViewProjection viewProjection);
	~Skydome() { delete modelSkydome; }

private:
	WorldTransform worldTransform_;
	Model* modelSkydome = nullptr;
	float size = 100.0f;
};