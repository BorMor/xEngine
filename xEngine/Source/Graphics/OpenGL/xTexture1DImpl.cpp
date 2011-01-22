#include "xEngine.h"
#include "xPrerequisites.h"
#include "xTextureImpl.h"

xTexture1D::xTexture1D(xUInt32 width, xUInt32 miplevels, xTextureFormat::Enum format)
	: xTexture(format, miplevels), mWidth(width)
{	
}

xTexture1D::~xTexture1D()
{
}

void xTexture1D::SetImage(xUInt16 level, void* data, size_t sz)
{
	if (mMipLevels == 0 && level > 0)
		return;
	GLint internal_format = GetInternalFormat(mFormat);
	glBindTexture(GL_TEXTURE_1D, pImpl->mTexture);
	
	xUInt32 width = mWidth;
	for (size_t i = 0; i < level; i++)
	{
		if (width > 1)
			width >>= 1;
	}

	if (mFormat >= xTextureFormat::DXT1 && mFormat <= xTextureFormat::DXT5)
		glCompressedTexImage1D(GL_TEXTURE_1D, level, internal_format, width, 0, sz, data);
	else
	{
		GLenum data_format, data_type;
		GetDataFormat(mFormat, data_format, data_type);
		glTexImage1D(GL_TEXTURE_1D, level, internal_format, width, 0, data_format, data_type, data);
	}
	if (mMipLevels == 0 && level == 0)
		glGenerateMipmap(GL_TEXTURE_1D);
	glBindTexture(GL_TEXTURE_1D, 0);
}

void xTexture1D::SetSubImage(xUInt16 level, xUInt16 x, xUInt16 width, void* data, size_t sz)
{
	glBindTexture(GL_TEXTURE_1D, pImpl->mTexture);
	if (mFormat >= xTextureFormat::DXT1 && mFormat <= xTextureFormat::DXT5)
	{		
		GLint internal_format = GetInternalFormat(mFormat);
		glCompressedTexSubImage1D(GL_TEXTURE_1D, level, x, width, internal_format, sz, data);
	}
	else
	{
		GLenum data_format, data_type;
		GetDataFormat(mFormat, data_format, data_type);
		glTexSubImage1D(GL_TEXTURE_1D, level, x, width, data_format, data_type, data);
	}
	glBindTexture(GL_TEXTURE_1D, 0);
}