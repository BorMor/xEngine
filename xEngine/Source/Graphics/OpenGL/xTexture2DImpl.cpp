#include "xEngine.h"
#include "xPrerequisites.h"

struct xTexture2D::Impl
{
	GLuint	mTexture;
};


GLint GetInternalFormat(xTextureFormat::Enum format)
{
	switch (format)
	{
	case xTextureFormat::R8:
		return GL_RED;
	case xTextureFormat::R16:
		return GL_R16;
	case xTextureFormat::R8G8:
		return GL_RG8;
	case xTextureFormat::R16G16:
		return GL_RG16;
	case xTextureFormat::R8G8B8A8:
		return GL_RGBA8;
	case xTextureFormat::R16G16B16A16:
		return GL_RGBA16;
	case xTextureFormat::R10G10B10A2:
		return GL_RGB10_A2;
	case xTextureFormat::R16_FLOAT:
		return GL_R16F;
	case xTextureFormat::R16G16_FLOAT:
		return GL_RG16F;
	case xTextureFormat::R16G16B16A16_FLOAT:
		return GL_RGBA16F;
	case xTextureFormat::R32_FLOAT:
		return GL_R32F;
	case xTextureFormat::R32G32_FLOAT:
		return GL_RG32F;
	case xTextureFormat::R32G32B32_FLOAT:
		return GL_RGB32F;
	case xTextureFormat::R32G32B32A32_FLOAT:
		return GL_RGBA32F;	
	case xTextureFormat::DXT1:
		return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	case xTextureFormat::DXT3:
		return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	case xTextureFormat::DXT5:
		return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	default:
		break;		
	}
	return 0;
}

void GetDataFormat(xTextureFormat::Enum format, GLenum& data_format, GLenum& data_type)
{
	switch (format)
	{
	case xTextureFormat::R8:
		data_format = GL_RED;
		data_type = GL_UNSIGNED_BYTE;
		break;
	case xTextureFormat::R16:
		data_format = GL_RED;
		data_type = GL_UNSIGNED_SHORT;
		break;
	case xTextureFormat::R8G8:
		data_format = GL_RG;
		data_type = GL_UNSIGNED_BYTE;
		break;
	case xTextureFormat::R16G16:
		data_format = GL_RG;
		data_type = GL_UNSIGNED_SHORT;
		break;
	case xTextureFormat::R8G8B8A8:
		data_format = GL_RGBA;
		data_type = GL_UNSIGNED_BYTE;
		break;
	case xTextureFormat::R16G16B16A16:
		data_format = GL_RGBA;
		data_type = GL_UNSIGNED_SHORT;
		break;
	case xTextureFormat::R10G10B10A2:
		data_format = GL_RGBA;
		data_type = GL_UNSIGNED_INT_10_10_10_2;
		break;
	case xTextureFormat::R16_FLOAT:
		data_format = GL_RED;
		data_type = GL_FLOAT;
		break;
	case xTextureFormat::R16G16_FLOAT:
		data_format = GL_RG;
		data_type = GL_FLOAT;
		break;
	case xTextureFormat::R16G16B16A16_FLOAT:
		data_format = GL_RGBA;
		data_type = GL_FLOAT;
		break;
	case xTextureFormat::R32_FLOAT:
		data_format = GL_RED;
		data_type = GL_FLOAT;
		break;
	case xTextureFormat::R32G32_FLOAT:
		data_format = GL_RG;
		data_type = GL_FLOAT;
		break;
	case xTextureFormat::R32G32B32_FLOAT:
		data_format = GL_RGB;
		data_type = GL_FLOAT;
		break;
	case xTextureFormat::R32G32B32A32_FLOAT:
		data_format = GL_RGBA;
		data_type = GL_FLOAT;		
		break;
	default:
		break;		
	}	
}

xTexture2D::xTexture2D(xUInt32 width, xUInt32 height, xUInt32 miplevels, xTextureFormat::Enum format)
	: mWidth(width), mHeight(height), mMipLevels(miplevels), mFormat(format)
{
	pImpl = new Impl();
	glGenTextures(1, &pImpl->mTexture);
	glBindTexture(GL_TEXTURE_2D, pImpl->mTexture);
}

xTexture2D::~xTexture2D()
{
	glDeleteTextures(1, &pImpl->mTexture);
	xSAFE_DELETE(pImpl);
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
	int err = glGetError();
	if (mMipLevels == 0 && level == 0)
		glGenerateMipmap(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, 0);
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
	glBindTexture(GL_TEXTURE_2D, 0);
}