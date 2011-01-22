#pragma once

class xEXPORT xTexture
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;	
public:
	xTexture(xTextureFormat::Enum format, xUInt32 miplevels);
	virtual ~xTexture();

	xTextureFormat::Enum Format() const;

	static xTexture* LoadFromFile(const xString& path);
protected:	
	xUInt32					mMipLevels;
	xTextureFormat::Enum	mFormat;
};

xEXPORT
size_t xGetImageSize(xTextureFormat::Enum format, xUInt32 width, xUInt32 height);