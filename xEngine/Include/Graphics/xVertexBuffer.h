#pragma once

class xEXPORT xVertexBuffer
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;	
public:
	xVertexBuffer(xSharedPtr<xVertexFormat> vertex_format, size_t vertex_count, size_t stride);
	~xVertexBuffer();

	size_t Stride() const;
	size_t VertexCount() const;
	size_t SizeInBytes() const;


	void* Lock();
	void Unlock();

	static xVertexBuffer* LoadFromStream(xStream* stream);
protected:
	size_t	mStride;
	size_t	mVertexCount;
};

typedef xSharedPtr<xVertexBuffer> xVertexBufferPtr;
