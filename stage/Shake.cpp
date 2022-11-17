#include "Shake.h"
#include <random>

void Shake::ShakeStart(float shakeStrength)
{
	if (isShake_) { return; }
	shakeStrength_ = shakeStrength;
	isShake_ = true;
}

void Shake::Update(ViewProjection& viewProjection)
{
	if (!isShake_) { return; }
	static std::random_device randam;
	std::mt19937_64 engine(randam());
	static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	shakeVec_ = { dist(engine),dist(engine) ,dist(engine) };
	shakeVec_ *= shakeStrength_--;

	viewProjection.target += shakeVec_;
	viewProjection.eye += shakeVec_;

	if (shakeStrength_ <= 0.01f) { isShake_ = false; }
}