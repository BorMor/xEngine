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
	xString mode;
	switch (mAccessMode){
		case xAccessMode::Read:
			mode = "r";
			break;
		case xAccessMode::Write:
			mode = "w";
			break;
		case xAccessMode::ReadWrite:
			mode = "a+";
			break;
	}

	pImpl->mHandle = fopen(mFileName.c_str(), mode.c_str());
	if (pImpl->mHandle != NULL) mIsOpen = true;
	else throw;
}

void xFileStream::Close(){
	if ((mIsOpen) && (fclose(pImpl->mHandle) == 0)) mIsOpen = false;
}

void xFileStream::Seek(size_t offset, xSeekOrigin::Enum origin){
	if (!mIsOpen) throw;
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
	if (!mIsOpen) throw;
	return fread(buffer, 1, count, pImpl->mHandle);
}

size_t xFileStream::Write(void* buffer, size_t count){
	if (!mIsOpen) throw;
	return fwrite(buffer, 1, count, pImpl->mHandle);
}

size_t xFileStream::Size() const
{
	if (!mIsOpen) throw;
	size_t cur = ftell(pImpl->mHandle);
	fseek(pImpl->mHandle, 0, SEEK_END);
	size_t end = ftell(pImpl->mHandle);
	fseek(pImpl->mHandle, cur, SEEK_SET);
	return end;
}
