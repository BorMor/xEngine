#pragma once

class xEXPORT xFileStream : public xStream
{
	xHIDE_IMPLEMENTATION
public:
	xFileStream(const xString& filename, xAccessMode::Enum access_mode);
	~xFileStream();

	void Open();
	void Close();

	void Seek(size_t offset, xSeekOrigin::Enum origin);
	size_t Read(void* buffer, size_t count);
	size_t Write(void* buffer, size_t count);
protected:
	xString mFileName;
};