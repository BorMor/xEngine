xFORCE_INLINE
xVector3::xVector3()
{
}

xFORCE_INLINE
xVector3::xVector3(float x, float y, float z)
	: X(x), Y(y), Z(z)
{
}

xFORCE_INLINE
xVector3::xVector3(const xVector3& other)
	: X(other.X), Y(other.Y), Z(other.Z)
{
}

xFORCE_INLINE
xVector3 xVector3::operator + (const xVector3& other) const
{
	return xVector3(X + other.X, Y + other.Y, Z + other.Z);
}

xFORCE_INLINE
xVector3& xVector3::operator += (const xVector3& other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	return (*this);
}

xFORCE_INLINE
xVector3 xVector3::operator - (const xVector3& other) const
{
	return xVector3(X - other.X, Y - other.Y, Z - other.Z);
}

xFORCE_INLINE
xVector3& xVector3::operator -= (const xVector3& other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	return (*this);
}

xFORCE_INLINE
xVector3 xVector3::operator - () const
{
	return xVector3(-X, -Y, -Z);
}

xFORCE_INLINE
bool xVector3::operator == (const xVector3& other) const
{
	return (X == other.X && Y == other.Y && Z == other.Z);
}

xFORCE_INLINE
bool xVector3::operator != (const xVector3& other) const
{
	return (X != other.X || Y != other.Y || Z != other.Z);
}

xFORCE_INLINE
xVector3& xVector3::operator *= (float f)
{
	X *= f;
	Y *= f;
	Z *= f;
	return *this;
}

xFORCE_INLINE
xVector3 xVector3::operator * (float f) const
{
	return xVector3(X*f, Y*f, Z*f);
}

xFORCE_INLINE
float xVector3::SquaredLength() const
{
	return X*X + Y*Y + Z*Z;
}

xFORCE_INLINE
float xVector3::Length() const
{
	return sqrtf(SquaredLength());
}

xFORCE_INLINE
xVector3& xVector3::Normalize()
{
	float l = Length();
	if (l > 0.0001f)
	{
		X /= l;
		Y /= l;
		Z /= l;
	}
	return *this;
}


//////////////////////////////////////////////////////////////////////////
// функции
//////////////////////////////////////////////////////////////////////////


xFORCE_INLINE
float dot(const xVector3& a, const xVector3& b)
{
	return a.X*b.X + a.Y*b.Y + a.Z*b.Z;
}

xFORCE_INLINE
xVector3 cross(const xVector3& a, const xVector3& b)
{
	return xVector3(a.Y*b.Z - b.Y*a.Z , a.Z*b.X-b.Z*a.X , a.X*b.Y-b.X*a.Y );
}


xFORCE_INLINE
xVector3 normalize(const xVector3& v)
{
	xVector3 nv(v);
	return nv.Normalize();
}
