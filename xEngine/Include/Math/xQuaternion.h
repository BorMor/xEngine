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

	// Norm(q) - возвращает норму кватерниона x*x + y*y + z*z + w*w, для единичного кватерниона Norm(q)=1
	float Norm() const;

	// |q| - возвращает модуль кватерниона sqrt( Norm(q) )
	float Magnitude() const;

	// сопряжение - задает вращение обратное данному [v, -w]
	xQuaternion& Conjugate();

	// q^-1 инвертирует кватернион, conjugate(q)/norm(q), для единичного кватерниона inverse=conjugate
	xQuaternion& Inverse();

	//нормализует кватернион
	xQuaternion& Normalize();

	//поворачивает вектор данным кватернионом
	xVector3& Rotate(xVector3& v) const;

	float X;
	float Y;
	float Z;
	float W;

	static const xQuaternion IDENTITY;
};


//скалярное произведение кватернионов
float dot(const xQuaternion& a, const xQuaternion& b);

//поворот вектора v кватернионом q
xVector3 rotate(const xVector3& v, const xQuaternion& q);

//возвращает кватернион, задающий обратное вращение
xQuaternion conjugate(const xQuaternion& q);

//возвращает инверсный кватернион
xQuaternion inverse(const xQuaternion& q);

#include "xQuaternion.inl"
