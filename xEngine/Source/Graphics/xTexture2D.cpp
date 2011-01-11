#include "xEngine.h"

xUInt32 xTexture2D::Width() const
{
	return mWidth;
}

xUInt32 xTexture2D::Height() const
{
	return mHeight;
}

#define DDS_MAGIC ('D'|('D'<<8)|('S'<<16)|(' '<<24))
#define DDS_DXT1  ('D'|('X'<<8)|('T'<<16)|('1'<<24))
#define DDS_DXT3  ('D'|('X'<<8)|('T'<<16)|('3'<<24))
#define DDS_DXT5  ('D'|('X'<<8)|('T'<<16)|('5'<<24))

#define DDS_FOURCC  0x00000004
#define DDS_RGB     0x00000040
#define DDS_RGBA    0x00000041
#define DDS_VOLUME  0x00200000
#define DDS_CUBEMAP 0x00000200

struct DDSHeader
{
  xUInt32 Size;
  xUInt32 Flags;
  xUInt32 Height;
  xUInt32 Width;
  xUInt32 PitchLinearSize;
  xUInt32 Depth;
  xUInt32 MipMapCount;
  xUInt32 Reserved1[11];
  xUInt32 pfSize;
  xUInt32 pfFlags;
  xUInt32 pfFourCC;
  xUInt32 pfRGBBitCount;
  xUInt32 pfRMask;
  xUInt32 pfGMask;
  xUInt32 pfBMask;
  xUInt32 pfAMask;
  xUInt32 Caps1;
  xUInt32 Caps2;
  xUInt32 Reserved2[3];
};

xTexture2D* xTexture2D::LoadFromFile(const xString& path)
{
	xStreamPtr stream = new xFileStream(path, xAccessMode::Read);
	xBinaryReader reader(stream);
	xUInt32 magic = reader.ReadUInt32();
	if (magic != DDS_MAGIC)
		return NULL;
	DDSHeader header;
	reader.Read(&header, sizeof(DDSHeader));

	xTextureFormat::Enum format;
	
	if (header.pfFlags & DDS_FOURCC)
	{
		switch(header.pfFourCC)
		{
		case DDS_DXT1:
			format = xTextureFormat::DXT1;
			break;
		case DDS_DXT3:
			format = xTextureFormat::DXT3;
			break;
		case DDS_DXT5:
			format = xTextureFormat::DXT5;
			break;
		default:
			xLog << "xTexture2D::LoadFromFile(\"" << path << "\" : Unsupported DXT compression" << xEndl;
			return NULL;
		}
	}
	else
	{
		xLog << "xTexture2D::LoadFromFile(\"" << path << "\" : Unsupported DXT texture format" << xEndl;
	}
	
	xTexture2D* texture = new xTexture2D(header.Width, header.Height, header.MipMapCount, format);
	void* data = 0;
	xUInt32 w = header.Width;
	xUInt32 h = header.Height;
	for (size_t i = 0; i < header.MipMapCount; i++)
	{
		size_t sz = format == xTextureFormat::DXT1 ? ((w+3)/4)*((h+3)/4)*8 : ((w+3)/4)*((h+3)/4)*16;
		if (!data)
			data = malloc(sz);
		reader.Read(data, sz);
		texture->SetImage(i, data, sz);
		if (w > 1)
			w >>= 1;
		if (h > 1)
			h >>= 1;
	}
	if (data)
		free(data);

	return texture;
}