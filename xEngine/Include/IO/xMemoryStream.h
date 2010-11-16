#pragma once

class xEXPORT xMemoryStream : public xStream
{
public:
	xMemoryStream(void* buffer, size_t size, xAccessMode::Enum access_mode);
	~xMemoryStream();


	void Seek(size_t offset, xSeekOrigin::Enum origin);
	size_t Read(void* buffer, size_t count);
	size_t Write(void* buffer, size_t count);
	size_t Size() const;
protected:
	xByte*	mBuffer;
	xByte*	mPtr;
	size_t	mSize;
};