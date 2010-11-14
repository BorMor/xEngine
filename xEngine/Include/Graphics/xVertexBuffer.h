#pragma once

class xEXPORT xVertexBuffer
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;	
public:
	xVertexBuffer(xVertexFormat* vertex_format, size_t vertex_count, size_t stride = 0);
	~xVertexBuffer();

	size_t Stride() const;
	size_t VertexCount() const;
	size_t SizeInBytes() const;
	void* Lock();
	void Unlock();
protected:
	size_t	mStride;
	size_t	mVertexCount;
};

typedef xSharedPtr<xVertexBuffer> xVertexBufferPtr;
