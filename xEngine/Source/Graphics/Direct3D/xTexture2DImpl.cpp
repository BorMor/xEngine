#include "xEngine.h"
#include "xPrerequisites.h"

struct xTexture2D::Impl
{
	ID3D10Texture2D*			mTexture;
	ID3D10ShaderResourceView*	mShaderResourceView;
};

DXGI_FORMAT GetPixelFormat(xTextureFormat::Enum format)
{
	switch (format)
	{
	case xTextureFormat::R8:
		return DXGI_FORMAT_R8_UNORM;
	case xTextureFormat::R16:
		return DXGI_FORMAT_R16_UNORM;
	case xTextureFormat::R8G8:
		return DXGI_FORMAT_R8G8_UNORM;
	case xTextureFormat::R16G16:
		return DXGI_FORMAT_R16G16_UNORM;
	case xTextureFormat::R8G8B8A8:
		return DXGI_FORMAT_R8G8B8A8_UNORM;
	case xTextureFormat::R16G16B16A16:
		return DXGI_FORMAT_R16G16B16A16_UNORM;
	case xTextureFormat::R10G10B10A2:
		return DXGI_FORMAT_R10G10B10A2_UNORM;
	case xTextureFormat::R16_FLOAT:
		return DXGI_FORMAT_R16_FLOAT;
	case xTextureFormat::R16G16_FLOAT:
		return DXGI_FORMAT_R16G16_FLOAT;
	case xTextureFormat::R16G16B16A16_FLOAT:
		return DXGI_FORMAT_R16G16B16A16_FLOAT;
	case xTextureFormat::R32_FLOAT:
		return DXGI_FORMAT_R32_FLOAT;
	case xTextureFormat::R32G32_FLOAT:
		return DXGI_FORMAT_R32G32_FLOAT;
	case xTextureFormat::R32G32B32_FLOAT:
		return DXGI_FORMAT_R32G32B32_FLOAT;
	case xTextureFormat::R32G32B32A32_FLOAT:
		return DXGI_FORMAT_R32G32B32A32_FLOAT;
	case xTextureFormat::DXT1:
		return DXGI_FORMAT_BC1_UNORM;
	case xTextureFormat::DXT3:
		return DXGI_FORMAT_BC2_UNORM;
	case xTextureFormat::DXT5:
		return DXGI_FORMAT_BC3_UNORM;
	default:
		return DXGI_FORMAT_UNKNOWN;
	}	
}

xTexture2D::xTexture2D(xUInt32 width, xUInt32 height, xUInt32 miplevels, xTextureFormat::Enum format)
	: mWidth(width), mHeight(height), mMipLevels(miplevels), mFormat(format)
{
	pImpl = new Impl();
	D3D10_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(D3D10_TEXTURE2D_DESC));

	desc.Width = width;
	desc.Height = height;
	desc.ArraySize = 1;
	desc.Format = GetPixelFormat(format);	
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D10_USAGE_DEFAULT;
	desc.BindFlags = D3D10_BIND_SHADER_RESOURCE;
	HRESULT hr = gDevice->CreateTexture2D(&desc, NULL, &pImpl->mTexture);
	hr = gDevice->CreateShaderResourceView(pImpl->mTexture, 0, &pImpl->mShaderResourceView);
}

xTexture2D::~xTexture2D()
{
	pImpl->mShaderResourceView->Release();
	pImpl->mTexture->Release();
	xSAFE_DELETE(pImpl);
}

void xTexture2D::SetImage(xUInt16 level, void* data, size_t sz)
{
	if (mMipLevels == 0 && level > 0)
		return;
	xUInt32 width = mWidth;
	for (size_t i = 0; i < level; i++)
	{
		if (width > 1)
			width >>= 1;
	}
	UINT rowpitch =  max(1, (width + 3) / 4)*16; //hardcoded, dxt5
	
	gDevice->UpdateSubresource(pImpl->mTexture, level, 0, data, rowpitch, 0);
}

void xTexture2D::SetSubImage(xUInt16 level, xUInt16 x, xUInt16 y, xUInt16 width, xUInt16 height, void* data, size_t sz)
{
	D3D10_BOX box;
	box.left = x;
	box.top = y;
	box.front = 0;
	box.right = x + width;		//what for width <4 ??
	box.bottom = y + height;
	box.back = 0;
	
	UINT rowpitch =  max(1, (width + 3) / 4)*16; //hardcoded, dxt5
	
	gDevice->UpdateSubresource(pImpl->mTexture, level, &box, data, rowpitch, 0);
}