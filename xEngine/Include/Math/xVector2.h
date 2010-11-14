#pragma once

class xEXPORT xVector2
{
public:
	xVector2();
	xVector2(float x, float y);
	xVector2(const xVector2& other);

	xVector2 operator + (const xVector2& other) const;
	xVector2& operator += (const xVector2& other);
	xVector2 operator - (const xVector2& other) const;
	xVector2& operator -= (const xVector2& other);
	xVector2 operator - () const;

	bool operator == (const xVector2& other) const;
	bool operator != (const xVector2& other) const;

	xVector2& operator *= (float f);
	xVector2 operator * (float f) const;

	float SquaredLength() const;
	float Length() const;
	xVector2& Normalize();

	float X;
	float Y;

	static const xVector2 ZERO;
};

#include "xVector2.inl"
