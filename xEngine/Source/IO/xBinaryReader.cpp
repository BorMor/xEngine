#include "xEngine.h"

xBinaryReader::xBinaryReader(xStream* stream)
	: mStream(stream)
{
}

xBinaryReader::~xBinaryReader()
{
}

void xBinaryReader::Read(void* buffer, size_t count)
{
	mStream->Read(buffer, count);
}

xByte xBinaryReader::ReadByte()
{
	xByte b;
	mStream->Read(&b, sizeof(xByte));
	return b;
}

xChar xBinaryReader::ReadChar()
{
	xChar c;
	mStream->Read(&c, sizeof(xChar));
	return c;
}

xUInt32 xBinaryReader::ReadUInt32()
{
	xUInt32 i;
	mStream->Read(&i, sizeof(xUInt32));
	return i;
}

xInt32 xBinaryReader::ReadInt32()
{
	xInt32 i;
	mStream->Read(&i, sizeof(xInt32));
	return i;
}

xUInt16 xBinaryReader::ReadUInt16()
{
	xUInt16 s;
	mStream->Read(&s, sizeof(xUInt16));
	return s;
}

xInt16 xBinaryReader::ReadInt16()
{
	xInt16 s;
	mStream->Read(&s, sizeof(xInt16));
	return s;
}

xFloat xBinaryReader::ReadFloat()
{
	xFloat f;
	mStream->Read(&f, sizeof(xFloat));
	return f;
}

xString xBinaryReader::ReadString()
{
	xString result;
	xUInt16 len = ReadUInt16();
	if (len > 0)
	{
		result.Reserve(len+1);
		xChar* buffer = (xChar*)result.c_str();
		mStream->Read(buffer, len);
		buffer[len] = 0;
	}
	return result;
}
