xFORCE_INLINE
xColor::xColor()
{
}

xFORCE_INLINE
xColor::xColor(xByte r, xByte g, xByte b, xByte a) : B(b), G(g), R(r), A(a)
{
}

xFORCE_INLINE
xUInt32 xColor::ARGB() const
{
	return (A << 24) | (R << 16) | (G << 8) | B;
}

xFORCE_INLINE
xUInt32 xColor::RGBA() const
{
	return (R << 24) | (G << 16) | (B << 8) | A;
}
