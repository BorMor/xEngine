#include "xEngine.h"
#include "xPrerequisites.h"

struct xTexture2D::Impl
{
	ID3D10Texture2D*	mTexture;
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
		return DXGI_FORMAT_BC3_UNORM;
	case xTextureFormat::DXT5:
		return DXGI_FORMAT_BC5_UNORM;
	default:
		return DXGI_FORMAT_UNKNOWN;
	}	
}

xTexture2D::xTexture2D(xUInt32 width, xUInt32 height, xUInt32 miplevels, xTextureFormat::Enum format)
	: mWidth(width), mHeight(height)
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
}

xTexture2D::~xTexture2D()
{
	pImpl->mTexture->Release();
	xSAFE_DELETE(pImpl);
}