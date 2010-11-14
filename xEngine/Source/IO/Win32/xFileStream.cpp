#include "xEngine.h"

struct xFileStream::Impl
{
	HANDLE	mHandle;
};

xFileStream::xFileStream(const xString& filename, xAccessMode::Enum access_mode)
	: xStream(access_mode), mFileName(filename)
{
	pImpl = new Impl;
	Open();
}

xFileStream::~xFileStream()
{
	Close();
	xSAFE_DELETE(pImpl);
}

void xFileStream::Open()
{
	DWORD access = 0;
	DWORD creation = 0;

	switch (mAccessMode)
	{
	case xAccessMode::Read:
		access = GENERIC_READ;
		creation = OPEN_EXISTING;
		break;
	case xAccessMode::Write:
		access = GENERIC_WRITE;
		creation = CREATE_ALWAYS;
		break;
	case xAccessMode::ReadWrite:
		access = GENERIC_READ | GENERIC_WRITE;
		creation = OPEN_ALWAYS;
		break;
	}
	
	pImpl->mHandle = CreateFile(mFileName.c_str(), access, FILE_SHARE_READ, NULL, creation, FILE_ATTRIBUTE_NORMAL, 0);
}

void xFileStream::Close()
{
	if (mIsOpen)
		CloseHandle(pImpl->mHandle);
}

void xFileStream::Seek(size_t offset, xSeekOrigin::Enum origin)
{
	DWORD _origin;
	switch (origin)
	{
	case xSeekOrigin::Begin:
		_origin = FILE_BEGIN;
		break;
	case xSeekOrigin::End:
		_origin = FILE_END;
		break;
	case xSeekOrigin::Current:		
	default:
		_origin = FILE_CURRENT;
	}
	SetFilePointer(pImpl->mHandle, (LONG)offset, NULL, _origin);//@todo SetFilePointerEx
}

size_t xFileStream::Read(void* buffer, size_t count)
{
	DWORD readed;
	ReadFile(pImpl->mHandle, buffer, (DWORD)count, &readed, NULL);
	return (size_t)readed;
}

size_t xFileStream::Write(void* buffer, size_t count)
{
	DWORD written;
	WriteFile(pImpl->mHandle, buffer, (DWORD)count, &written, NULL);
	return (size_t)written;
}
