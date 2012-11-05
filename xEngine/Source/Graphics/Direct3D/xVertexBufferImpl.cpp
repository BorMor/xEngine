#include "xEngine.h"
#include "xPrerequisites.h"
#include "xVertexBufferImpl.h"
#include "xVertexFormatImpl.h"

xVertexBuffer::xVertexBuffer(xSharedPtr<xVertexFormat> vertex_format, size_t vertex_count, size_t stride)
	: mStride(stride), mVertexCount(vertex_count)
{
	pImpl = new Impl;
	pImpl->mData = NULL;
	pImpl->mVertexFormat = vertex_format;

	D3D11_BUFFER_DESC desc;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = SizeInBytes();
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;	

	/*D3D11_SUBRESOURCE_DATA initial_data;
	initial_data.pSysMem = data;
	initial_data.SysMemPitch = 0;
	initial_data.SysMemSlicePitch = 0;*/

	gDevice->CreateBuffer(&desc, 0, &pImpl->mBuffer);		
}


xVertexBuffer::~xVertexBuffer()
{
	if (pImpl->mData)
		free(pImpl->mData);
	if (pImpl->mBuffer)
		pImpl->mBuffer->Release();
	xSAFE_DELETE(pImpl);
}

void* xVertexBuffer::Lock()
{
	if (pImpl->mData)
		free(pImpl->mData);
	pImpl->mData = malloc(SizeInBytes());
	//HRESULT hr = pImpl->mBuffer->Map(D3D11_MAP_WRITE_DISCARD, 0, &result);
	return pImpl->mData;
}

void xVertexBuffer::Unlock()
{
	if (pImpl->mData)
	{
		gDeviceContext->UpdateSubresource(pImpl->mBuffer, 0, NULL, pImpl->mData, 0, 0);//->UpdateSubresource(
		free(pImpl->mData);
		pImpl->mData = NULL;
	}
	//pImpl->mBuffer->Unmap();
}