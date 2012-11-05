#pragma once;

struct xTexture2D::Impl
{
	ID3D11Texture2D*			mTexture;
	ID3D11ShaderResourceView*	mShaderResourceView;
};