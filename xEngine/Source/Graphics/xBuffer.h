#pragma once

class xBuffer
{
public:
	xBuffer(size_t size_in_bytes);
	virtual ~xBuffer();	
	
	const void* Data() const;
	size_t SizeInBytes() const;

	void WriteData(size_t offset, void* data, size_t size);	
	virtual void Flush();
protected:	
	xByte*	mData;
	size_t	mSizeInBytes;
	bool	mChanged;
};
