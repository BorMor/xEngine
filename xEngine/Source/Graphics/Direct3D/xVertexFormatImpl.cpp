#include "xEngine.h"
#include "xVertexFormatImpl.h"

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