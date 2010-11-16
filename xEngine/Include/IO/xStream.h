#pragma once

struct xSeekOrigin
{
	enum Enum
	{
		Begin,
		Current,
		End
	};
};

struct xAccessMode
{
	enum Enum
	{
		Read,
		Write,
		ReadWrite
	};
};

class xEXPORT xStream
{
public:
	xStream(xAccessMode::Enum access_mode);
	virtual ~xStream();

	virtual void Open();
	virtual void Close();
	bool IsOpen() const;

	virtual void Seek(size_t offset, xSeekOrigin::Enum origin) = 0;
	virtual size_t Read(void* buffer, size_t count) = 0;
	virtual size_t Write(void* buffer, size_t count) = 0;
	virtual size_t Size() const = 0;
protected:
	xAccessMode::Enum mAccessMode;
	bool mIsOpen;
};

typedef xSharedPtr<xStream> xStreamPtr;