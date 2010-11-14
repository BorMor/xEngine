#include "xEngine.h"

void xString::FreeData()
{
	if (mData != mBaseBuffer)
		delete [] mData;
	mData = mBaseBuffer;
	mLength = 0;
	mAllocated = 0;
}

void xString::ReAlloc(size_t nbytes, bool keep_old)
{
	size_t amount = nbytes;
	size_t mod = amount % xSTRING_ALLOC_GRAN;
	if (mod != 0)
		amount = nbytes - mod + xSTRING_ALLOC_GRAN;

	xChar* newbuffer = new xChar[amount];
	if (keep_old)
		memcpy(newbuffer, mData, mLength+1);
	if (mData != mBaseBuffer)
		delete [] mData;
	mData = newbuffer;
	mAllocated = amount;
}

xString xString::Format(const xChar* format, ...)
{
    xChar buf[2048];

    va_list args;
    va_start(args, format);
#if defined(xPLATFORM_LINUX)
    vsnprintf(buf, sizeof(buf), format, args);
#else
	_vsnprintf(buf, sizeof(buf), format, args);
#endif
    va_end(args);

    return xString(buf);
}
