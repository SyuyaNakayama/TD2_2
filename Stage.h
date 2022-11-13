#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>
#include "Model.h"
#include "player/Player.h"
#include <memory>

class Stage
{
private:
	std::vector<WorldTransform> blocks_;
	Model* model_ = nullptr;
	const float POLE_RAD = 25.0f;
	std::unique_ptr<Player> player_ = nullptr;
	ViewProjection viewProjection_;

public:
	void Initialize(ViewProjection& viewProjection);
	void Update();
	void Draw();
};