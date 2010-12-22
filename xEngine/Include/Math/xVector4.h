#pragma once

class xEXPORT xVector4
{
public:
	xVector4();
	xVector4(float x, float y, float z, float w);
	xVector4(const xVector4& other);

	xVector4 operator + (const xVector4& other) const;
	xVector4& operator += (const xVector4& other);
	xVector4 operator - (const xVector4& other) const;
	xVector4& operator -= (const xVector4& other);
	xVector4 operator - () const;

	bool operator == (const xVector4& other) const;
	bool operator != (const xVector4& other) const;

	xVector4& operator *= (float f);
	xVector4 operator * (float f) const;

	float SquaredLength() const;
	float Length() const;
	xVector4& Normalize();

	float X;
	float Y;
	float Z;
	float W;

	static const xVector4 ZERO;
};

xVector4 normalize(const xVector4& v);

#include "xVector4.inl"
