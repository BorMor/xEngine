#pragma once

class xEXPORT xMatrix
{
public:
	xMatrix();
	xMatrix(	float m00, float m01, float m02, float m03,
							float m10, float m11, float m12, float m13,
							float m20, float m21, float m22, float m23,
							float m30, float m31, float m32, float m33);
	
	xMatrix(const xMatrix& other);

	xMatrix operator + (const xMatrix& other) const;
	xMatrix& operator += (const xMatrix& other);

	xMatrix operator * (const xMatrix& other) const;
	xMatrix& operator *= (const xMatrix& other);

	union
	{
		float M[4][4];
		struct
		{
			float M00, M01, M02, M03;
			float M10, M11, M12, M13;
			float M20, M21, M22, M23;
			float M30, M31, M32, M33;
		};
	};

	static const xMatrix IDENTITY;
};

class xProjectionMatrix : public xMatrix
{
public:
	xProjectionMatrix(float fovy, float aspect, float znear, float zfar);
};

class xViewMatrix : public xMatrix
{
public:
	xViewMatrix(const xVector3& eye, const xVector3& at, const xVector3& up);
};

#include "xMatrix.inl"
