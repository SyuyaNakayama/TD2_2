#pragma once
class Jamp
{
private:
	bool isJamp_ = false;
	float jampSpd_ = 0;
	float gravity = 0;
	float endHeight_ = 0;

public:
	void StartJamp(float jampV0, float gravityAcc,float endHeight);
	void Update(float& y);
	bool IsJamp() { return isJamp_; }
};