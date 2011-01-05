#include "xEngine.h"
#include "xPrerequisites.h"
#include "xIndexBufferImpl.h"


xIndexBuffer::xIndexBuffer(xIndexFormat::Enum format, size_t index_count)
	: mFormat(format), mIndexCount(index_count)
{
	pImpl = new Impl();
	
	glGenBuffers(1, &pImpl->mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pImpl->mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeInBytes(), NULL, GL_STATIC_DRAW);
}

xIndexBuffer::~xIndexBuffer()
{
	glDeleteBuffers(1, &pImpl->mIBO);
	xSAFE_DELETE(pImpl);
}

void* xIndexBuffer::Lock()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pImpl->mIBO);
	return glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void xIndexBuffer::Unlock()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pImpl->mIBO);
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
}
