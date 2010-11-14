#pragma once

struct xIndexFormat
{
	enum Enum
	{
		UInt16,
		UInt32
	};
};

class xEXPORT xIndexBuffer
{
	xHIDE_IMPLEMENTATION
public:
	xIndexBuffer(xIndexFormat::Enum format, size_t index_count);
	~xIndexBuffer();

	xIndexFormat::Enum Format() const;
	size_t SizeInBytes() const;    
	void* Lock();
	void Unlock();
protected:
	xIndexFormat::Enum	mFormat;
	size_t				mIndexCount;
};

typedef xSharedPtr<xIndexBuffer> xIndexBufferPtr;
