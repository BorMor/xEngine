xFORCE_INLINE
xMatrix::xMatrix()
{
}

xFORCE_INLINE
xMatrix::xMatrix(	float m00, float m01, float m02, float m03,
					float m10, float m11, float m12, float m13,
					float m20, float m21, float m22, float m23,
					float m30, float m31, float m32, float m33)
{
	M[0][0] = m00;	M[0][1] = m01;	M[0][2] = m02;	M[0][3] = m03;
	M[1][0] = m10;	M[1][1] = m11;	M[1][2] = m12;	M[1][3] = m13;
	M[2][0] = m20;	M[2][1] = m21;	M[2][2] = m22;	M[2][3] = m23;
	M[3][0] = m30;	M[3][1] = m31;	M[3][2] = m32;	M[3][3] = m33;
}

xFORCE_INLINE
xMatrix::xMatrix(const xMatrix& other)
{
	M00 = other.M00; M01 = other.M01; M02 = other.M02; M03 = other.M03;
	M10 = other.M10; M11 = other.M11; M12 = other.M12; M13 = other.M13;
	M20 = other.M20; M21 = other.M21; M22 = other.M22; M23 = other.M23;
	M30 = other.M30; M31 = other.M31; M32 = other.M32; M33 = other.M33;
}

xFORCE_INLINE
xMatrix xMatrix::operator + (const xMatrix& other) const
{
	return xMatrix(
		M00+other.M00, M01+other.M01, M02+other.M02, M03+other.M03,
		M10+other.M10, M11+other.M11, M12+other.M12, M13+other.M13,
		M20+other.M20, M21+other.M21, M22+other.M22, M23+other.M23,
		M30+other.M30, M31+other.M31, M32+other.M32, M33+other.M33
		);
}

xFORCE_INLINE
xMatrix& xMatrix::operator += (const xMatrix& other)
{
	M00+=other.M00; M01+=other.M01; M02+=other.M02; M03+=other.M03;
	M10+=other.M10; M11+=other.M11; M12+=other.M12; M13+=other.M13;
	M20+=other.M20; M21+=other.M21; M22+=other.M22; M23+=other.M23;
	M30+=other.M30; M31+=other.M31; M32+=other.M32; M33+=other.M33;
	return *this;
}

xFORCE_INLINE
xMatrix xMatrix::operator * (const xMatrix& other) const
{
	return xMatrix(
		M00*other.M00 + M01*other.M10 + M02*other.M20 + M03*other.M30,		M00*other.M01 + M01*other.M11 + M02*other.M21 + M03*other.M31,		M00*other.M02 + M01*other.M12 + M02*other.M22 + M03*other.M32,		M00*other.M03 + M01*other.M13 + M02*other.M23 + M03*other.M33,
		M10*other.M00 + M11*other.M10 + M12*other.M20 + M13*other.M30,		M10*other.M01 + M11*other.M11 + M12*other.M21 + M13*other.M31,		M10*other.M02 + M11*other.M12 + M12*other.M22 + M13*other.M32,		M10*other.M03 + M11*other.M13 + M12*other.M23 + M13*other.M33,
		M20*other.M00 + M21*other.M10 + M22*other.M20 + M23*other.M30,		M20*other.M01 + M21*other.M11 + M22*other.M21 + M23*other.M31,		M20*other.M02 + M21*other.M12 + M22*other.M22 + M23*other.M32,		M20*other.M03 + M21*other.M13 + M22*other.M23 + M23*other.M33,
		M30*other.M00 + M31*other.M10 + M32*other.M20 + M33*other.M30,		M30*other.M01 + M31*other.M11 + M32*other.M21 + M33*other.M31,		M30*other.M02 + M31*other.M12 + M02*other.M22 + M33*other.M32,		M30*other.M03 + M31*other.M13 + M32*other.M23 + M33*other.M33
		);
}

xFORCE_INLINE
xMatrix& xMatrix::operator *= (const xMatrix& other)
{
	*this = (*this)*other;
	return *this;
}



xFORCE_INLINE
xProjectionMatrix::xProjectionMatrix(float fovy, float aspect, float znear, float zfar)
{
	float r = fovy * 3.1415926f / 360.f;
	float h = cosf(r*0.5f) / sinf(r*0.5f);
	float w = zfar / (zfar - znear);
#if defined(xRENDERSYSTEM_OPENGL) // right-handed system
	float t = -1.f;
#else
	float t = 1.f;
#endif

	M[0][0] = h / aspect;	M[0][1] = 0.f;	M[0][2] = 0.f;		M[0][3] = 0.f;
	M[1][0] = 0.f;			M[1][1] = h;	M[1][2] = 0.f;		M[1][3] = 0.f;
	M[2][0] = 0.f;			M[2][1] = 0.f;	M[2][2] = w*t;		M[2][3] = t;
	M[3][0] = 0.f;			M[3][1] = 0.f;	M[3][2] = -znear*w;	M[3][3] = 0.f;
}

xFORCE_INLINE
xViewMatrix::xViewMatrix(const xVector3& eye, const xVector3& at, const xVector3& up)
{
	xVector3 zaxis = normalize(at - eye);
	xVector3 xaxis = normalize(cross(up, zaxis));
	xVector3 yaxis = cross(zaxis, xaxis);

	M[0][0] = xaxis.X;			M[0][1] = yaxis.X;			M[0][2] = zaxis.X;			M[0][3] = 0.f;
	M[1][0] = xaxis.Y;			M[1][1] = yaxis.Y;			M[1][2] = zaxis.Y;			M[1][3] = 0.f;
	M[2][0] = xaxis.Z;			M[2][1] = yaxis.Z;			M[2][2] = zaxis.Z;			M[2][3] = 0.f;
	M[3][0] = -dot(xaxis, eye);	M[3][1] = -dot(yaxis, eye);	M[3][2] = -dot(zaxis, eye);	M[3][3] = 1.f;
}
