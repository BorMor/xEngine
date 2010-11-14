xFORCE_INLINE
xPlane::xPlane(const xVector3& normal, float distance)
	: A(normal.X), B(normal.Y), C(normal.Z), D(distance)
{
}

xFORCE_INLINE
xPlane::xPlane(float a, float b, float c, float d)
	: A(a), B(b), C(c), D(d)
{
}

xFORCE_INLINE
xPlane::xPlane(const xVector3& p1, const xVector3& p2, const xVector3& p3)
{
	xVector3    p12(p2.X - p1.X, p2.Y - p1.Y, p2.Z - p1.Z);
	xVector3	p13(p3.X - p1.X, p3.Y - p1.Y, p3.Z - p1.Z);

	xVector3 normal = normalize(cross(p12, p13));
	A = normal.X;
	B = normal.Y;
	C = normal.Z;
	D = -dot(normal, p1);
}

xFORCE_INLINE
xVector3 xPlane::Normal() const
{
    return xVector3(A, B, C);
}

xFORCE_INLINE
float xPlane::Distance() const
{
    return D;
}

xFORCE_INLINE
float dot(const xPlane& plane, const xVector3& v)
{
	return (dot(plane.Normal(), v) + plane.D);
}
