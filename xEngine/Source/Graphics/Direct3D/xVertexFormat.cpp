#include "xEngine.h"
#include "xVertexFormatImpl.h"

size_t GetVertexElementSize(xVertexElementType::Enum type)
{
	switch (type)
	{
	case xVertexElementType::Vector2:
		return sizeof(xVector2);
	case xVertexElementType::Vector3:
		return sizeof(xVector3);
	case xVertexElementType::Color:
		return sizeof(xColor);
	case xVertexElementType::Float:
		return sizeof(xFloat);
		break;
	default:
		return 0;
	}
}

xVertexFormat::xVertexFormat()
	: mSize(0)
{
	pImpl = new Impl;
	pImpl->mLayout = 0;
}

xVertexFormat::~xVertexFormat()
{	
	if (pImpl->mLayout)
		pImpl->mLayout->Release();
	xSAFE_DELETE(pImpl);
}

void xVertexFormat::Clear()
{
	mElements.Clear();
	mSize = 0;
}

void xVertexFormat::AddElement(xVertexElementType::Enum type, xVertexElementUsage::Enum usage)
{	
	Element el;
	el.Offset = mSize;
	el.Type = type;
	el.Usage = usage;
	mElements.AddBack(el);
	mSize += GetVertexElementSize(type);	
}

size_t xVertexFormat::VertexSize() const
{
	return mSize;
}