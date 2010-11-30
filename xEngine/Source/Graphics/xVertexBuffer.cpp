#include "xEngine.h"

size_t xVertexBuffer::Stride() const
{
	return mStride;
}

size_t xVertexBuffer::VertexCount() const
{
	return mVertexCount;
}

size_t xVertexBuffer::SizeInBytes() const
{
    return mStride * mVertexCount;
}

xVertexBuffer* xVertexBuffer::LoadFromStream(xStream* stream)
{
	xBinaryReader reader(stream);
	reader.ReadUInt32();	// 'VBUF'
	xVertexFormat* format = new xVertexFormat;
	format->AddElement(xVertexElementType::Vector3, xVertexElementUsage::Position);
	format->AddElement(xVertexElementType::Vector3, xVertexElementUsage::Normal);
	xUInt32 vcount = reader.ReadUInt32();
	xUInt32 stride = 24;
	xVertexBuffer* buffer = new xVertexBuffer(format, vcount, stride);	
	void* data = buffer->Lock();
	reader.Read(data, vcount * stride);	
	buffer->Unlock();
	return buffer;
}