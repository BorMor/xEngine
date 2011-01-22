#include "xEngine.h"
#include "xPrerequisites.h"
#include "xTextureImpl.h"

xTexture1D::xTexture1D(xUInt32 width, xUInt32 miplevels, xTextureFormat::Enum format)
	: xTexture(format, miplevels), mWidth(width)
{
	D3D10_TEXTURE1D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D10_TEXTURE1D_DESC));

	desc.Width = width;
	desc.ArraySize = 1;
	desc.Format = GetPixelFormat(format);	
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	ID3D10Texture1D* texture = NULL;
	HRESULT hr = gDevice->CreateTexture1D(&desc, NULL, &texture);
	pImpl->mTexture = texture;
	hr = gDevice->CreateShaderResourceView(pImpl->mTexture, 0, &pImpl->mShaderResourceView);
}

xTexture1D::~xTexture1D()
{
}

void xTexture1D::SetImage(xUInt16 level, void* data, size_t sz)
{
	if (mMipLevels == 0 && level > 0)
		return;
	gDevice->UpdateSubresource(pImpl->mTexture, level, 0, data, GetRowPitch(mFormat, mWidth, level), 0);
}

void xTexture1D::SetSubImage(xUInt16 level, xUInt16 x, xUInt16 width, void* data, size_t sz)
{
	D3D10_BOX box;
	box.left = x;
	box.top = 0;
	box.front = 0;
	box.right = x + width;		//what for width <4 ??
	box.bottom = 1;
	box.back = 0;
	gDevice->UpdateSubresource(pImpl->mTexture, level, &box, data, GetRowPitch(mFormat, mWidth, level), 0);
}