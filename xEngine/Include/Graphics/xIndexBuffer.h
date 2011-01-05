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
	friend class xRenderDevice;
public:
	xIndexBuffer(xIndexFormat::Enum format, size_t index_count);
	~xIndexBuffer();

	xIndexFormat::Enum Format() const;
	size_t IndexCount() const;
	size_t SizeInBytes() const;    
	
	void* Lock();
	void Unlock();

	static xIndexBuffer* LoadFromStream(xStream* stream);
protected:
	xIndexFormat::Enum	mFormat;
	size_t				mIndexCount;
};

typedef xSharedPtr<xIndexBuffer> xIndexBufferPtr;
