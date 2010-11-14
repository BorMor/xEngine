xFORCE_INLINE
xVector2::xVector2()
{
}

xFORCE_INLINE
xVector2::xVector2(float x, float y)
	: X(x), Y(y)
{
}

xFORCE_INLINE
xVector2::xVector2(const xVector2& other)
	: X(other.X), Y(other.Y)
{
}

xFORCE_INLINE
xVector2 xVector2::operator + (const xVector2& other) const
{
	return xVector2(X + other.X, Y + other.Y);
}

xFORCE_INLINE
xVector2& xVector2::operator += (const xVector2& other)
{
	X += other.X;
	Y += other.Y;
	return (*this);
}

xFORCE_INLINE
xVector2 xVector2::operator - (const xVector2& other) const
{
	return xVector2(X - other.X, Y - other.Y);
}

xFORCE_INLINE
xVector2& xVector2::operator -= (const xVector2& other)
{
	X -= other.X;
	Y -= other.Y;
	return (*this);
}

xFORCE_INLINE
xVector2 xVector2::operator - () const
{
	return xVector2(-X, -Y);
}

xFORCE_INLINE
bool xVector2::operator == (const xVector2& other) const
{
	return (X == other.X && Y == other.Y);
}

xFORCE_INLINE
bool xVector2::operator != (const xVector2& other) const
{
	return (X != other.X || Y != other.Y);
}

xFORCE_INLINE
xVector2& xVector2::operator *= (float f)
{
	X *= f;
	Y *= f;
	return *this;
}

xFORCE_INLINE
xVector2 xVector2::operator * (float f) const
{
	return xVector2(X*f, Y*f);
}

xFORCE_INLINE
float xVector2::SquaredLength() const
{
	return X*X + Y*Y;
}

xFORCE_INLINE
float xVector2::Length() const
{
	return sqrtf(SquaredLength());
}

xFORCE_INLINE
xVector2& xVector2::Normalize()
{
	float l = Length();
	if (l > 0.0001f)
	{
		X /= l;
		Y /= l;
	}
	return *this;
}
