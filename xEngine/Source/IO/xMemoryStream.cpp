#include "xEngine.h"


xMemoryStream::xMemoryStream(void* buffer, size_t size, xAccessMode::Enum access_mode)
	: xStream(access_mode)
{
	mBuffer = (xByte*)buffer;
	mSize = size;
	mPtr = mBuffer;
}

xMemoryStream::~xMemoryStream()
{
}

void xMemoryStream::Seek(size_t offset, xSeekOrigin::Enum origin)
{
	switch (origin)
	{
	case xSeekOrigin::Begin:
		mPtr = mBuffer + offset;
		break;
	case xSeekOrigin::End:
		mPtr = mBuffer + mSize - offset;
		break;
	case xSeekOrigin::Current:		
		mPtr = mPtr + offset;
	}
}

size_t xMemoryStream::Read(void* buffer, size_t count)
{
	memcpy(buffer, mPtr, count);
	mPtr += count;
	return count;
}

size_t xMemoryStream::Write(void* buffer, size_t count)
{
	memcpy(mPtr, buffer, count);
	mPtr += count;
	return count;
}