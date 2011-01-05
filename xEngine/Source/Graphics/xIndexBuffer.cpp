#include "xEngine.h"


xIndexFormat::Enum xIndexBuffer::Format() const
{
	return mFormat;
}

size_t xIndexBuffer::IndexCount() const
{
	return mIndexCount;
}

size_t xIndexBuffer::SizeInBytes() const
{
	if (mFormat == xIndexFormat::UInt16)
		return 2*mIndexCount;
	else
		return 4*mIndexCount;
}


xIndexBuffer* xIndexBuffer::LoadFromStream(xStream* stream)
{
	xBinaryReader reader(stream);
	reader.ReadUInt32();	// 'IBUF'
	
	xIndexFormat::Enum format = (xIndexFormat::Enum)reader.ReadUInt16();
	xUInt32 icount = reader.ReadUInt32();	

	xIndexBuffer* buffer = new xIndexBuffer(format, icount);
	void* data = buffer->Lock();
	reader.Read(data, buffer->SizeInBytes());	
	buffer->Unlock();
	return buffer;
}