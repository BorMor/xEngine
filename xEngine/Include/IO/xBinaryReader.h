#pragma once

class xEXPORT xBinaryReader
{
public:
	xBinaryReader(xStream* stream);
	~xBinaryReader();

	void Read(void* buffer, size_t count);
	xByte ReadByte();
	xChar ReadChar();
	xUInt32 ReadUInt32();
	xInt32 ReadInt32();
	xUInt16 ReadUInt16();
	xInt16 ReadInt16();
	xFloat ReadFloat();
	xString ReadString();
protected:
	xStream* mStream;
};