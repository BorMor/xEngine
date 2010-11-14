#pragma once

class xEXPORT xVector3
{
public:
	xVector3();
	xVector3(float x, float y, float z);
	xVector3(const xVector3& other);

	xVector3 operator + (const xVector3& other) const;
	xVector3& operator += (const xVector3& other);
	xVector3 operator - (const xVector3& other) const;
	xVector3& operator -= (const xVector3& other);
	xVector3 operator - () const;

	bool operator == (const xVector3& other) const;
	bool operator != (const xVector3& other) const;

	xVector3& operator *= (float f);
	xVector3 operator * (float f) const;

	float SquaredLength() const;
	float Length() const;
	xVector3& Normalize();

	float X;
	float Y;
	float Z;

	static const xVector3 ZERO;
};


//скалярное произведение векторов
float dot(const xVector3& a, const xVector3& b);

//векторное произведение векторов
xVector3 cross(const xVector3& a, const xVector3& b);

//нормализованный вектор
xVector3 normalize(const xVector3& v);

#include "xVector3.inl"
