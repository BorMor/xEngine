#pragma once

class xEXPORT xTexture1D : public xTexture
{		
public:
	xTexture1D(xUInt32 width, xUInt32 miplevels, xTextureFormat::Enum format);
	~xTexture1D();	

	xUInt32 Width() const;

	void SetImage(xUInt16 level, void* data, size_t sz);
	void SetSubImage(xUInt16 level, xUInt16 x,xUInt16 width, void* data, size_t sz);	
protected:	
	xUInt32					mWidth;
};
