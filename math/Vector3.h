#pragma once

class Vector3
{
public:
	float x, y, z;
public:
	Vector3();
	Vector3(float x, float y, float z);

	float length() const; // �m����(����)
	Vector3& normalize(); // ���K��
	float dot(const Vector3& v) const; // ���ϒl
	Vector3 cross(const Vector3& v) const; // �O�ϒl
	Vector3 abs();

	// �P�����Z�q�I�[�o�[���[�h
	Vector3 operator+() const;
	Vector3 operator-() const;

	// ������Z�q�I�[�o�[���[�h
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);

	bool operator<=(Vector3);
	bool operator>=(Vector3);
	bool operator<(Vector3);
	bool operator>(Vector3);
	bool operator==(Vector3);
};