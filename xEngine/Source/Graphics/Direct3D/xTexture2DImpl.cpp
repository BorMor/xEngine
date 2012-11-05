#include "xEngine.h"
#include "xPrerequisites.h"
#include "xTextureImpl.h"

xTexture2D::xTexture2D(xUInt32 width, xUInt32 height, xUInt32 miplevels, xTextureFormat::Enum format)
	: xTexture(format, miplevels), mWidth(width), mHeight(height)
{
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));

	desc.Width = width;
	desc.Height = height;
	desc.ArraySize = 1;
	desc.Format = GetPixelFormat(format);	
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	ID3D11Texture2D* texture = NULL;
	HRESULT hr = gDevice->CreateTexture2D(&desc, NULL, &texture);
	pImpl->mTexture = texture;
	hr = gDevice->CreateShaderResourceView(pImpl->mTexture, 0, &pImpl->mShaderResourceView);
}

xTexture2D::~xTexture2D()
{
}

void xTexture2D::SetImage(xUInt16 level, void* data, size_t sz)
{
	if (mMipLevels == 0 && level > 0)
		return;
	gDeviceContext->UpdateSubresource(pImpl->mTexture, level, 0, data, GetRowPitch(mFormat, mWidth, level), 0);
}

void xTexture2D::SetSubImage(xUInt16 level, xUInt16 x, xUInt16 y, xUInt16 width, xUInt16 height, void* data, size_t sz)
{
	D3D11_BOX box;
	box.left = x;
	box.top = y;
	box.front = 0;
	box.right = x + width;		//what for width <4 ??
	box.bottom = y + height;
	box.back = 0;
	gDeviceContext->UpdateSubresource(pImpl->mTexture, level, &box, data, GetRowPitch(mFormat, mWidth, level), 0);
}