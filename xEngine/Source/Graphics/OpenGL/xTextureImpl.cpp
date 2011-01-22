#include "xEngine.h"
#include "xPrerequisites.h"
#include "xTextureImpl.h"


xTexture::xTexture(xTextureFormat::Enum format, xUInt32 miplevels)
	: mFormat(format), mMipLevels(miplevels)
{
	pImpl = new Impl();
	glGenTextures(1, &pImpl->mTexture);
}

xTexture::~xTexture()
{
	glDeleteTextures(1, &pImpl->mTexture);
	xSAFE_DELETE(pImpl);
}