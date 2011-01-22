#include "xEngine.h"
#include "xPrerequisites.h"
#include "xTextureImpl.h"

xTexture2D::xTexture2D(xUInt32 width, xUInt32 height, xUInt32 miplevels, xTextureFormat::Enum format)
	: xTexture(format, miplevels), mWidth(width), mHeight(height)
{	
}

xTexture2D::~xTexture2D()
{
}

void xTexture2D::SetImage(xUInt16 level, void* data, size_t sz)
{
	if (mMipLevels == 0 && level > 0)
		return;
	GLint internal_format = GetInternalFormat(mFormat);
	glBindTexture(GL_TEXTURE_2D, pImpl->mTexture);
	
	xUInt32 width = mWidth;
	xUInt32 height = mHeight;
	for (size_t i = 0; i < level; i++)
	{
		if (width > 1)
			width >>= 1;
		if (height > 1)
			height >>= 1;
	}

	if (mFormat >= xTextureFormat::DXT1 && mFormat <= xTextureFormat::DXT5)
		glCompressedTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height, 0, sz, data);
	else
	{
		GLenum data_format, data_type;
		GetDataFormat(mFormat, data_format, data_type);
		glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height, 0, data_format, data_type, data);
	}
	if (mMipLevels == 0 && level == 0)
		glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void xTexture2D::SetSubImage(xUInt16 level, xUInt16 x, xUInt16 y, xUInt16 width, xUInt16 height, void* data, size_t sz)
{
	glBindTexture(GL_TEXTURE_2D, pImpl->mTexture);
	if (mFormat >= xTextureFormat::DXT1 && mFormat <= xTextureFormat::DXT5)
	{		
		GLint internal_format = GetInternalFormat(mFormat);
		glCompressedTexSubImage2D(GL_TEXTURE_2D, level, x, y, width, height, internal_format, sz, data);
	}
	else
	{
		GLenum data_format, data_type;
		GetDataFormat(mFormat, data_format, data_type);
		glTexSubImage2D(GL_TEXTURE_2D, level, x, y, width, height, data_format, data_type, data);
	}
	if (mMipLevels == 0 && level == 0)
		glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}