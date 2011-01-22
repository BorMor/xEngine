#pragma once;

struct xTexture2D::Impl
{
	ID3D10Texture2D*			mTexture;
	ID3D10ShaderResourceView*	mShaderResourceView;
};