xFORCE_INLINE
xString::xString()
{
	Init();
}

xFORCE_INLINE
xString::xString(const xString& other)
{
	Init();
	Set(other.mData, other.mLength);
}

xFORCE_INLINE
xString::xString(xString&& other)
{
	Init();
	if (other.mData == other.mBaseBuffer)
		memcpy(mData, other.mData, xSTRING_ALLOC_BASE);
	else
		mData = other.mData;
	mLength = other.mLength;
	mAllocated = other.mAllocated;
	other.mData = other.mBaseBuffer;
}

xFORCE_INLINE
xString::xString(const xChar* text)
{
	Init();
	Set(text, strlen(text));
}

xFORCE_INLINE
xString::xString(const xChar* text, size_t length)
{
	Init();
	Set(text, length);
}

xFORCE_INLINE
xString::~xString()
{
	FreeData();
}

xFORCE_INLINE
void xString::Init()
{
	mData = mBaseBuffer;
	memset(mBaseBuffer, 0, xSTRING_ALLOC_BASE);
	mLength = 0;
	mAllocated = 0;
}

xFORCE_INLINE
void xString::EnsureAllocated(size_t nbytes, bool keep_old)
{
	if (nbytes > xSTRING_ALLOC_BASE && nbytes > mAllocated)
		ReAlloc(nbytes, keep_old);
}

xFORCE_INLINE
void xString::Set(const xString& str)
{
	Set(str.mData, str.mLength);
}

xFORCE_INLINE
void xString::Set(const xChar* text)
{
	size_t length = strlen(text);
	EnsureAllocated(length+1, false);
	memcpy(mData, text, length);
	mData[length] = 0;
	mLength = length;
}

xFORCE_INLINE
void xString::Set(const xChar* text, size_t length)
{
	if (length > 0)
	{
		EnsureAllocated(length+1, false);
		memcpy(mData, text, length);
	}
	mData[length] = 0;
	mLength = length;
}

xFORCE_INLINE
void xString::Append(const xString& str)
{
	Append(str.mData, str.mLength);
}

xFORCE_INLINE
void xString::Append(const xChar* text, size_t length)
{
	EnsureAllocated(mLength+length+1, true);
	memcpy(mData+mLength, text, length);
	mLength += length;
	mData[mLength] = 0;
}

xFORCE_INLINE
void xString::Append(const xChar c)
{
	EnsureAllocated(mLength+2, true);
	mData[mLength] = c;
	mLength += 1;
	mData[mLength] = 0;
}

xFORCE_INLINE
void xString::Reserve(size_t nbytes)
{
	mLength = nbytes-1;
	EnsureAllocated(nbytes, false);
}

xFORCE_INLINE
xString& xString::operator =(const xString& text)
{
	Set(text);
	return *this;
}

xFORCE_INLINE
xString& xString::operator +=(const xString& text)
{
	Append(text);
	return *this;
}

xFORCE_INLINE
xString& xString::operator +=(const char* text)
{
	Append(text, strlen(text));
	return *this;
}

xFORCE_INLINE
xString& xString::operator +=(const char c)
{
	Append(c);
	return *this;
}

xFORCE_INLINE
const xChar* xString::c_str() const
{
	return mData;
}

xFORCE_INLINE
void* xString::Data()
{
	return mData;
}

xFORCE_INLINE
xChar& xString::operator[](int index)
{
	return mData[index];
}

xFORCE_INLINE
const xChar& xString::operator[](int index) const
{
	return mData[index];
}
xFORCE_INLINE
xString xString::SubString(size_t index, size_t length)
{
	xString result;
	result.Reserve(length+1);
	memcpy(result.mData, mData + index, length);
	result.mData[length] = 0;
	return result;
}

xFORCE_INLINE
size_t xString::Length() const
{
	return mLength;
}

xFORCE_INLINE
xString operator+(const xString& a, const xString& b)
{
	xString result(a);
	result.Append(b);
	return result;
}

xFORCE_INLINE
bool operator ==( const xString& a, const xString& b)
{
	return strcmp(a.mData, b.mData) == 0;
}

xFORCE_INLINE
bool operator !=( const xString& a, const xString& b)
{
	return strcmp(a.mData, b.mData) != 0;
}

xFORCE_INLINE
bool operator <(const xString& a, const xString& b)
{
	return strcmp(a.mData, b.mData) < 0;
}

xFORCE_INLINE
bool operator >(const xString& a, const xString& b)
{
	return strcmp(a.mData, b.mData) > 0;
}