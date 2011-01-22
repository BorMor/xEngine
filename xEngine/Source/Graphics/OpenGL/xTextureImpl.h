#pragma once

struct xTexture::Impl
{
	GLuint	mTexture;
};

xFORCE_INLINE
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

xFORCE_INLINE
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