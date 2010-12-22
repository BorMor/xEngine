xFORCE_INLINE
xVector4::xVector4()
{
}

xFORCE_INLINE
xVector4::xVector4(float x, float y, float z, float w)
	: X(x), Y(y), Z(z), W(w)
{
}

xFORCE_INLINE
xVector4::xVector4(const xVector4& other)
	: X(other.X), Y(other.Y), Z(other.Z), W(other.W)
{
}

xFORCE_INLINE
xVector4 xVector4::operator + (const xVector4& other) const
{
	return xVector4(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
}

xFORCE_INLINE
xVector4& xVector4::operator += (const xVector4& other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	W += other.W;
	return (*this);
}

xFORCE_INLINE
xVector4 xVector4::operator - (const xVector4& other) const
{
	return xVector4(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
}

xFORCE_INLINE
xVector4& xVector4::operator -= (const xVector4& other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	W -= other.W;
	return (*this);
}

xFORCE_INLINE
xVector4 xVector4::operator - () const
{
	return xVector4(-X, -Y, -Z, -W);
}

xFORCE_INLINE
bool xVector4::operator == (const xVector4& other) const
{
	return (X == other.X && Y == other.Y && Z == other.Z && W == other.W);
}

xFORCE_INLINE
bool xVector4::operator != (const xVector4& other) const
{
	return (X != other.X || Y != other.Y || Z != other.Z || W != other.W);
}

xFORCE_INLINE
xVector4& xVector4::operator *= (float f)
{
	X *= f;
	Y *= f;
	Z *= f;
	W *= f;
	return *this;
}

xFORCE_INLINE
xVector4 xVector4::operator * (float f) const
{
	return xVector4(X*f, Y*f, Z*f, W*f);
}

xFORCE_INLINE
float xVector4::SquaredLength() const
{
	return X*X + Y*Y + Z*Z + W*W;
}

xFORCE_INLINE
float xVector4::Length() const
{
	return sqrtf(SquaredLength());
}

xFORCE_INLINE
xVector4& xVector4::Normalize()
{
	float l = Length();
	if (l > 0.0001f)
	{
		X /= l;
		Y /= l;
		Z /= l;
		W /= l;
	}
	return *this;
}

xFORCE_INLINE
xVector4 normalize(const xVector4& v)
{
	xVector4 nv(v);
	return nv.Normalize();
}
