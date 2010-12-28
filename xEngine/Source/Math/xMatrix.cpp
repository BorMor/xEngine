#include "xEngine.h"

const xMatrix xMatrix::IDENTITY(1.f, 0.f, 0.f, 0.f,
								0.f, 1.f, 0.f, 0.f,
								0.f, 0.f, 1.f, 0.f,
								0.f, 0.f, 0.f, 1.f);

void xBuildProjectionMatrix(xMatrix& matrix, float fovy, float aspect, float znear, float zfar)
{
	float r = fovy * 0.5f * 3.1415926f / 180.f;
	float h = cosf(r) / sinf(r);
	float w = 1 / (znear - zfar);

	matrix.M[0][0] = h / aspect;	matrix.M[0][1] = 0.f;	matrix.M[0][2] = 0.f;				matrix.M[0][3] = 0.f;
	matrix.M[1][0] = 0.f;			matrix.M[1][1] = h;		matrix.M[1][2] = 0.f;				matrix.M[1][3] = 0.f;
	matrix.M[2][0] = 0.f;			matrix.M[2][1] = 0.f;	matrix.M[2][2] = zfar*w;			matrix.M[2][3] = -1.f;
	matrix.M[3][0] = 0.f;			matrix.M[3][1] = 0.f;	matrix.M[3][2] = znear*zfar*w;		matrix.M[3][3] = 0.f;
}

void xBuildViewMatrix(xMatrix& matrix, const xVector3& eye, const xVector3& at, const xVector3& up)
{
	xVector3 zaxis = normalize(eye - at);
	xVector3 xaxis = normalize(cross(up, zaxis));
	xVector3 yaxis = cross(zaxis, xaxis);

	matrix.M[0][0] = xaxis.X;			matrix.M[0][1] = yaxis.X;			matrix.M[0][2] = zaxis.X;			matrix.M[0][3] = 0.f;
	matrix.M[1][0] = xaxis.Y;			matrix.M[1][1] = yaxis.Y;			matrix.M[1][2] = zaxis.Y;			matrix.M[1][3] = 0.f;
	matrix.M[2][0] = xaxis.Z;			matrix.M[2][1] = yaxis.Z;			matrix.M[2][2] = zaxis.Z;			matrix.M[2][3] = 0.f;
	matrix.M[3][0] = -dot(xaxis, eye);	matrix.M[3][1] = -dot(yaxis, eye);	matrix.M[3][2] = -dot(zaxis, eye);	matrix.M[3][3] = 1.f;
}