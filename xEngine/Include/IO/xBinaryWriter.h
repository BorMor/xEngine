#pragma once

class xEXPORT xBinaryWriter
{
public:
	xBinaryWriter(xStream* stream);
	~xBinaryWriter();

	void Write(void* buffer, size_t count);
	void WriteByte(xByte b);
	void WriteChar(xChar c);
	void WriteUInt32(xUInt32 i);
	void WriteInt32(xInt32 i);
	void WriteUInt16(xUInt16 i);
	void WriteInt16(xInt16 i);
	void WriteFloat(xFloat f);
	void WriteString(const xString& string);
protected:
	xStream* mStream;
};