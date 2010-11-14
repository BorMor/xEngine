#pragma once

struct xEXPORT xPlane
{
	xPlane(const xVector3& normal, float distance);
	xPlane(float a, float b, float c, float d);
	xPlane(const xVector3& p1, const xVector3& p2, const xVector3& p3);

	float	A;
    float	B;
    float	C;
    float	D;

    xVector3 Normal() const;
    float Distance() const;
};

float dot(const xPlane& plane, const xVector3& v);

#include "xPlane.inl"
