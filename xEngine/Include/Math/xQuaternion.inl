xFORCE_INLINE
xQuaternion::xQuaternion()
	: X(0), Y(0), Z(0), W(1)
{
}

xFORCE_INLINE
xQuaternion::xQuaternion(float x, float y, float z, float w)
	: X(x), Y(y), Z(z), W(w)
{
}

xFORCE_INLINE
xQuaternion::xQuaternion(const xQuaternion& other)
	: X(other.X), Y(other.Y), Z(other.Z), W(other.W)
{
}


xFORCE_INLINE
xQuaternion::xQuaternion(const xVector3& axis, float angle)
	: X(axis.X), Y(axis.Y), Z(axis.Z), W(0)
{
	float half_angle = angle * 0.5f;
	float xsin = sinf(half_angle);

	X *= xsin;
	Y *= xsin;
	Z *= xsin;
	W = cosf(angle * 0.5f);
	Normalize();
}

xFORCE_INLINE
xQuaternion::xQuaternion(const xVector3& from, const xVector3& to)
{
	xVector3 c = cross(from, to);
	float d = dot(from, to);

	X = c.X;
	Y = c.Y;
	Z = c.Z;
	W = d;

	Normalize();//?
	W+=1.0f;

	if (W <= 0.0001f)
	{
		if( ( from.Z*from.Z ) > ( from.X*from.X ) )
		{
			X=0.0f;
			Y=from.Z;
			Z=-from.Y;
		}
		else
		{
			X=from.Y;
			Y=-from.X;
			Z=0.0f;
		}
	}

	Normalize();//?
}

xFORCE_INLINE
xQuaternion xQuaternion::operator + (const xQuaternion& other) const
{
	return xQuaternion(X+other.X, Y+other.Y, Z+other.Z, W+other.W);
}

xFORCE_INLINE
xQuaternion& xQuaternion::operator += (const xQuaternion& other)
{
	X+=other.X;
	Y+=other.Y;
	Z+=other.Z;
	W+=other.W;
	return *this;
}

xFORCE_INLINE
xQuaternion xQuaternion::operator - (const xQuaternion& other) const
{
	return xQuaternion(X-other.X, Y-other.Y, Z-other.Z, W-other.W);
}

xFORCE_INLINE
xQuaternion& xQuaternion::operator -= (const xQuaternion& other)
{
	X-=other.X;
	Y-=other.Y;
	Z-=other.Z;
	W-=other.W;
	return *this;
}

xFORCE_INLINE
xQuaternion xQuaternion::operator * (const xQuaternion& other) const
{
	return xQuaternion(
		W*other.X + X*other.W + Y*other.Z - Z*other.Y,
		W*other.Y + Y*other.W + Z*other.X - X*other.Z,
		W*other.Z + Z*other.W + X*other.Y - Y*other.X,
		W*other.W - X*other.X - Y*other.Y - Z*other.Z);
}


xFORCE_INLINE
xQuaternion& xQuaternion::operator *= (const xQuaternion& other)
{
	float newX = W*other.X + X*other.W + Y*other.Z - Z*other.Y;
	float newY = W*other.Y + Y*other.W + Z*other.X - X*other.Z;
	float newZ = W*other.Z + Z*other.W + X*other.Y - Y*other.X;
	float newW = W*other.W - X*other.X - Y*other.Y - Z*other.Z;
	X = newX;
	Y = newY;
	Z = newZ;
	W = newW;
	return *this;
}


xFORCE_INLINE
xQuaternion xQuaternion::operator * (float scalar) const
{
	return xQuaternion(X*scalar, Y*scalar, Z*scalar, W*scalar);
}

xFORCE_INLINE
xQuaternion& xQuaternion::operator *= (float scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
	W *= scalar;
	return *this;
}


xFORCE_INLINE
xVector3& xQuaternion::operator * (xVector3& v) const
{
	return Rotate(v);
}

xFORCE_INLINE
float xQuaternion::Norm() const
{
	return X*X + Y*Y + Z*Z + W*W;
}

xFORCE_INLINE
float xQuaternion::Magnitude() const
{
	return sqrtf(Norm());
}

xFORCE_INLINE
xQuaternion& xQuaternion::Conjugate()
{
	W = -W;
	return *this;
}

xFORCE_INLINE
xQuaternion& xQuaternion::Inverse()
{
	float norm = Norm();
	if (norm > 0.0001f)
	{
		Conjugate();
		X /= norm;
		Y /= norm;
		Z /= norm;
		W /= norm;
	}
	else *this = IDENTITY;
	return *this;
}

xFORCE_INLINE
xQuaternion& xQuaternion::Normalize()
{
	float m = Magnitude();
	if (m > 0.0001f)
	{
		X /= m;
		Y /= m;
		Z /= m;
		W /= m;
	}
	else *this = IDENTITY;
	return *this;
}


xFORCE_INLINE
xVector3& xQuaternion::Rotate(xVector3 &v) const
{
	xQuaternion vq (v.X, v.Y, v.Z, 0);
	xQuaternion inverseq(X, Y, Z, -W);

	vq = (*this)*vq*inverseq;

	v.X = vq.X;
	v.Y = vq.Y;
	v.Z = vq.Z;

	return v;
}



//////////////////////////////////////////////////////////////////////////
//функции
//////////////////////////////////////////////////////////////////////////

xFORCE_INLINE
float dot(const xQuaternion& a, const xQuaternion& b)
{
	return a.X*b.X + a.Y*b.Y + a.Z*b.Z + a.W*b.W;
}

xFORCE_INLINE
xVector3 rotate(const xVector3& v, const xQuaternion& q)
{
	xVector3 newv(v);
	return q.Rotate(newv);
}

xFORCE_INLINE
xQuaternion conjugate(const xQuaternion& q)
{
	xQuaternion newq(q);
	return newq.Conjugate();
}

xFORCE_INLINE
xQuaternion inverse(const xQuaternion& q)
{
	xQuaternion newq(q);
	return newq.Inverse();
}
