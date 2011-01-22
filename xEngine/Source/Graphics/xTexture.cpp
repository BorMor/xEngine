#include "xEngine.h"

xTextureFormat::Enum xTexture::Format() const
{
	return mFormat;
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

size_t GetImageSize(xTextureFormat::Enum format, xUInt32 width, xUInt32 height)
{
	switch (format)
	{
	case xTextureFormat::DXT1:
		return ((width+3)/4)*((height+3)/4)*8;
	case xTextureFormat::DXT3:
	case xTextureFormat::DXT5:
		return ((width+3)/4)*((height+3)/4)*16;
	default:
		return 0;
	}
}

xTexture* xTexture::LoadFromFile(const xString& path)
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
			xLog << "xTexture::LoadFromFile(\"" << path << "\" : Unsupported DXT compression" << xEndl;
			return NULL;
		}
	}
	else
	{
		xLog << "xTexture::LoadFromFile(\"" << path << "\" : Unsupported DXT texture format" << xEndl;
	}
		
	if (header.Height != 1 && header.Depth == 0)
	{
		xTexture2D* texture = new xTexture2D(header.Width, header.Height, header.MipMapCount, format);
		void* data = 0;
		xUInt32 w = header.Width;
		xUInt32 h = header.Height;
		size_t levels = header.MipMapCount != 0 ? header.MipMapCount : 1;
		for (size_t i = 0; i < levels; i++)
		{
			size_t sz = GetImageSize(format, w, h);
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

	return NULL;
}