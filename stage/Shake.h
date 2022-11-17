#pragma once
#include "ViewProjection.h"

class Shake
{
private:
	bool isShake_ = false;
	Vector3 shakeVec_{};
	float shakeStrength_ = 0;

public:
	void ShakeStart(float shakeStrength);
	void Update(ViewProjection& viewProjection);
};

