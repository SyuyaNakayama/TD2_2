#include "MathUtility.h"

Matrix4 MathUtility::Matrix4Scaling(Vector3 scale) { return Matrix4Scaling(scale.x, scale.y, scale.z); }
Matrix4 MathUtility::Matrix4Rotation(Vector3 angle)
{
	return
		Matrix4RotationX(angle.x) *
		Matrix4RotationY(angle.y) *
		Matrix4RotationZ(angle.z);
}
Matrix4 MathUtility::Matrix4Translation(Vector3 translation) { return Matrix4Translation(translation.x, translation.y, translation.z); }
float MathUtility::DegreeToRadian(float angle_d) { return PI / 180.0f; }
float MathUtility::RadianToDegree(float angle_r) { return 180.0f / PI; }
Vector3 GetWorldTranslation(Matrix4 matWorld) { return Vector3(matWorld.m[3][0], matWorld.m[3][1], matWorld.m[3][2]); }