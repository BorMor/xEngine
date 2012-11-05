#pragma once;

struct xTexture::Impl
{
	ID3D11Resource*				mTexture;
	ID3D11ShaderResourceView*	mShaderResourceView;
};

xFORCE_INLINE
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

xFORCE_INLINE
UINT GetRowPitch(xTextureFormat::Enum format, xUInt32 width, xUInt32 level)
{
	for (size_t i = 0; i < level; i++)
	{
		if (width > 1)
			width >>= 1;
	}
	switch (format)
	{
	case xTextureFormat::R8:
		return width;
	case xTextureFormat::R16:
		return width*2;
	case xTextureFormat::R8G8:
		return width*2;
	case xTextureFormat::R16G16:
		return width*4;
	case xTextureFormat::R8G8B8A8:
		return width*4;
	case xTextureFormat::R16G16B16A16:
		return width*8;
	case xTextureFormat::R10G10B10A2:
		return width*4;
	case xTextureFormat::R16_FLOAT:
		return width*2;
	case xTextureFormat::R16G16_FLOAT:
		return width*4;
	case xTextureFormat::R16G16B16A16_FLOAT:
		return width*8;
	case xTextureFormat::R32_FLOAT:
		return width*4;
	case xTextureFormat::R32G32_FLOAT:
		return width*8;
	case xTextureFormat::R32G32B32_FLOAT:
		return width*12;
	case xTextureFormat::R32G32B32A32_FLOAT:
		return width*16;
	case xTextureFormat::DXT1:
		return max(1, (width + 3) / 4)*8;
	case xTextureFormat::DXT3:
	case xTextureFormat::DXT5:
		return max(1, (width + 3) / 4)*16;
	default:
		return 0;
	}
}