#include "xEngine.h"
#include "../xConstantBuffer.h"
#include "xConstantBufferImpl.h"

xConstantBuffer::xConstantBuffer(size_t size_in_bytes)
	: xBuffer(size_in_bytes)
{
	pImpl = new Impl();
	glGenBuffers(1, &pImpl->mUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, pImpl->mUBO);
	glBufferData(GL_UNIFORM_BUFFER, size_in_bytes, NULL, GL_STATIC_DRAW);
	
}

xConstantBuffer::~xConstantBuffer()
{
	glDeleteBuffers(1, &pImpl->mUBO);
	xSAFE_DELETE(pImpl);
}

void xConstantBuffer::Flush()
{
	glBindBuffer(GL_UNIFORM_BUFFER, pImpl->mUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, mSizeInBytes, mData);
}