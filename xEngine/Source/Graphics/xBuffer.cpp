#include "xEngine.h"
#include "xBuffer.h"

xBuffer::xBuffer(size_t size_in_bytes)
	: mChanged(false), mSizeInBytes(size_in_bytes)
{
	mData = new xByte[mSizeInBytes];
}

xBuffer::~xBuffer()
{
	xSAFE_ARRAY_DELETE(mData);
}

const void* xBuffer::Data() const
{
	return mData;
}

size_t xBuffer::SizeInBytes() const
{
	return mSizeInBytes;
}

void xBuffer::WriteData(size_t offset, void* data, size_t size)
{
	mChanged = true;
	memcpy((xByte*)mData + offset, data, size);
}

void xBuffer::Flush()
{
	mChanged = false;
}