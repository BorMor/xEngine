#pragma once

class xEXPORT xQuaternion
{
public:
	xQuaternion();
	xQuaternion(float x, float y, float z, float w);
	xQuaternion(const xQuaternion& other);
	xQuaternion(const xVector3& axis, float angle);
	xQuaternion(const xVector3& from, const xVector3& to);

	xQuaternion operator + (const xQuaternion& other) const;
	xQuaternion& operator += (const xQuaternion& other);

	xQuaternion operator - (const xQuaternion& other) const;
	xQuaternion& operator -= (const xQuaternion& other);

	xQuaternion operator * (const xQuaternion& other) const;
	xQuaternion& operator *= (const xQuaternion& other);

	xQuaternion operator * (float scalar) const;
	xQuaternion& operator *= (float scalar);

	xVector3& operator * (xVector3& v) const;

	// Norm(q) - ���������� ����� ����������� x*x + y*y + z*z + w*w, ��� ���������� ����������� Norm(q)=1
	float Norm() const;

	// |q| - ���������� ������ ����������� sqrt( Norm(q) )
	float Magnitude() const;

	// ���������� - ������ �������� �������� ������� [v, -w]
	xQuaternion& Conjugate();

	// q^-1 ����������� ����������, conjugate(q)/norm(q), ��� ���������� ����������� inverse=conjugate
	xQuaternion& Inverse();

	//����������� ����������
	xQuaternion& Normalize();

	//������������ ������ ������ ������������
	xVector3& Rotate(xVector3& v) const;

	float X;
	float Y;
	float Z;
	float W;

	static const xQuaternion IDENTITY;
};


//��������� ������������ ������������
float dot(const xQuaternion& a, const xQuaternion& b);

//������� ������� v ������������ q
xVector3 rotate(const xVector3& v, const xQuaternion& q);

//���������� ����������, �������� �������� ��������
xQuaternion conjugate(const xQuaternion& q);

//���������� ��������� ����������
xQuaternion inverse(const xQuaternion& q);

#include "xQuaternion.inl"
