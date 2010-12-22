#include "xEngine.h"
//#include "xPrerequisites.h"

struct xIndexBuffer::Impl
{
};

xIndexBuffer::xIndexBuffer(xIndexFormat::Enum format, size_t index_count)
	: mFormat(format), mIndexCount(index_count)
{
	pImpl = new Impl();
	/*
	glGenBuffersARB(1, &pImpl->mId);
    glBindBufferARB(GL_ARRAY_BUFFER_ARB, pImpl->mId);*/
}

xIndexBuffer::~xIndexBuffer()
{
	//glDeleteBuffersARB(1, &pImpl->mId);
	xSAFE_DELETE(pImpl);
}

xIndexFormat::Enum xIndexBuffer::Format() const
{
	return mFormat;
}

size_t xIndexBuffer::SizeInBytes() const
{
	if (mFormat == xIndexFormat::UInt16)
		return 2*mIndexCount;
	else
		return 4*mIndexCount;
}

void* xIndexBuffer::Lock()
{
    /*glBindBufferARB(GL_ARRAY_BUFFER_ARB, pImpl->mId);
	return glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_READ_WRITE_ARB);*/
	return 0;
}

void xIndexBuffer::Unlock()
{
    /*glBindBufferARB(GL_ARRAY_BUFFER_ARB, pImpl->mId);
    glUnmapBufferARB(GL_ARRAY_BUFFER_ARB);*/
}
