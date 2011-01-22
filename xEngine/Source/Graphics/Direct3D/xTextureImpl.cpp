#include "xEngine.h"
#include "xPrerequisites.h"
#include "xTextureImpl.h"


xTexture::xTexture(xTextureFormat::Enum format, xUInt32 miplevels)
	: mFormat(format), mMipLevels(miplevels)
{
	pImpl = new Impl();
	pImpl->mTexture = NULL;
	pImpl->mShaderResourceView = NULL;
}

xTexture::~xTexture()
{
	if (pImpl->mShaderResourceView)
		pImpl->mShaderResourceView->Release();
	if (pImpl->mTexture)
		pImpl->mTexture->Release();
	xSAFE_DELETE(pImpl);
}