#pragma once

class xEXPORT xTexture2D
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;	
public:
	xTexture2D(xUInt32 width, xUInt32 height, xUInt32 miplevels, xTextureFormat::Enum format);
	~xTexture2D();	

	xUInt32 Width() const;
	xUInt32 Height() const;

	void SetImage(xUInt16 level, void* data, size_t sz);
	void SetSubImage(xUInt16 level, xUInt16 x, xUInt16 y, xUInt16 width, xUInt16 height, void* data, size_t sz);

	static xTexture2D* LoadFromFile(const xString& path);
protected:	
	xUInt32					mWidth;
	xUInt32					mHeight;
	xUInt32					mMipLevels;
	xTextureFormat::Enum	mFormat;
};
