#include "xEngine.h"

struct xFileStream::Impl{
	FILE* mHandle;
};

xFileStream::xFileStream(const xString& filename, xAccessMode::Enum access_mode)
	: xStream(access_mode), mFileName(filename)
{
	pImpl = new Impl;
	Open();
}

xFileStream::~xFileStream(){
	Close();
	xSAFE_DELETE(pImpl);
}

void xFileStream::Open(){
	char mode;
	switch (mAccessMode){
		case xAccessMode::Read:
			mode = 'r';
			break;
		case xAccessMode::Write:
			mode = 'w';
			break;
		case xAccessMode::ReadWrite:
			mode = 'a';
			break;
	}

	pImpl->mHandle = fopen(mFileName.c_str(), &mode);
	if (pImpl->mHandle != NULL) mIsOpen = true;
}

void xFileStream::Close(){
	if ((mIsOpen) && (fclose(pImpl->mHandle) == 0)) mIsOpen = false;
}

void xFileStream::Seek(size_t offset, xSeekOrigin::Enum origin){
	xInt32 whence;
	switch (origin){
		case xSeekOrigin::Begin:
			whence = SEEK_SET;
			break;
		case xSeekOrigin::End:
			whence = SEEK_END;
			break;
		case xSeekOrigin::Current:
		default:
			whence = SEEK_CUR;
	}
	fseek(pImpl->mHandle, offset, whence);
}

size_t xFileStream::Read(void* buffer, size_t count){
	return fread(buffer, 1, count, pImpl->mHandle);
}

size_t xFileStream::Write(void* buffer, size_t count){
	return fwrite(buffer, 1, count, pImpl->mHandle);
}

// TODO: Реализовать нормально
size_t xFileStream::Size() const
{
	return 0;
}
