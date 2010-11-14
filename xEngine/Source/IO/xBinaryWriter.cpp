#include "xEngine.h"

xBinaryWriter::xBinaryWriter(xStream* stream)
	: mStream(stream)
{
}

xBinaryWriter::~xBinaryWriter()
{
}

void xBinaryWriter::Write(void* buffer, size_t count)
{
	mStream->Write(buffer, count);
}

void xBinaryWriter::WriteByte(xByte b)
{
	mStream->Write(&b, sizeof(xByte));
}

void xBinaryWriter::WriteChar(xChar c)
{
	mStream->Write(&c, sizeof(xChar));
}

void xBinaryWriter::WriteUInt32(xUInt32 i)
{
	mStream->Write(&i, sizeof(xUInt32));
}

void xBinaryWriter::WriteInt32(xInt32 i)
{
	mStream->Write(&i, sizeof(xInt32));
}

void xBinaryWriter::WriteUInt16(xUInt16 i)
{
	mStream->Write(&i, sizeof(xUInt16));
}

void xBinaryWriter::WriteInt16(xInt16 i)
{
	mStream->Write(&i, sizeof(xInt16));
}

void xBinaryWriter::WriteFloat(xFloat f)
{
	mStream->Write(&f, sizeof(xFloat));
}

void xBinaryWriter::WriteString(const xString& string)
{
	xUInt16 length = (xUInt16)string.Length();
	WriteUInt16(length);
	mStream->Write((void*)string.c_str(), length);
}