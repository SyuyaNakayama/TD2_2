#include "Jamp.h"

void Jamp::StartJamp(float jampV0, float gravityAcc, float endHeight)
{
    if (isJamp_) { return; }
    jampSpd_ = jampV0;
    gravity = gravityAcc;
    endHeight_ = endHeight;
    isJamp_ = true;
}

void Jamp::Update(float& y)
{
    if (!isJamp_) { return; }
    y += jampSpd_+ gravity;
    jampSpd_ -= gravity;
    if (y < endHeight_) 
    {
        y = endHeight_;
        isJamp_ = false; 
    }
}