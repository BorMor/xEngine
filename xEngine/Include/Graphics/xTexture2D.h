#pragma once

class xEXPORT xTexture2D : public xTexture
{		
public:
	xTexture2D(xUInt32 width, xUInt32 height, xUInt32 miplevels, xTextureFormat::Enum format);
	~xTexture2D();	

	xUInt32 Width() const;
	xUInt32 Height() const;

	void SetImage(xUInt16 level, void* data, size_t sz);
	void SetSubImage(xUInt16 level, xUInt16 x, xUInt16 y, xUInt16 width, xUInt16 height, void* data, size_t sz);	
protected:	
	xUInt32					mWidth;
	xUInt32					mHeight;
};
