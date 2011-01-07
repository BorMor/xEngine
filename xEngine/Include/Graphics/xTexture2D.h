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

	static xTexture2D* LoadFromFile(const xString& path);
protected:
	xUInt32 mWidth;
	xUInt32 mHeight;
};
