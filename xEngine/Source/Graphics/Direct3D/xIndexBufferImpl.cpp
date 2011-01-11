#include "xEngine.h"
#include "xPrerequisites.h"
#include "xIndexBufferImpl.h"

xIndexBuffer::xIndexBuffer(xIndexFormat::Enum format, size_t index_count)
	: mFormat(format), mIndexCount(index_count)
{
	pImpl = new Impl();
	pImpl->mData = NULL;

	D3D10_BUFFER_DESC desc;
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.ByteWidth = SizeInBytes();
	desc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;	

	HRESULT hr = gDevice->CreateBuffer(&desc, 0, &pImpl->mBuffer);		
}

xIndexBuffer::~xIndexBuffer()
{
	if (pImpl->mData)
		free(pImpl->mData);
	if (pImpl->mBuffer)
		pImpl->mBuffer->Release();
	xSAFE_DELETE(pImpl);
}

void* xIndexBuffer::Lock()
{
    if (pImpl->mData)
		free(pImpl->mData);
	pImpl->mData = malloc(SizeInBytes());
	return pImpl->mData;
}

void xIndexBuffer::Unlock()
{
	if (pImpl->mData)
	{
		gDevice->UpdateSubresource(pImpl->mBuffer, 0, NULL, pImpl->mData, 0, 0);
		free(pImpl->mData);
		pImpl->mData = NULL;
	}
}
