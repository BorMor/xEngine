#include "xEngine.h"

struct xVertexFormat::Impl
{
};

xVertexFormat::xVertexFormat()
	: mSize(0), pImpl(0)
{
}

xVertexFormat::~xVertexFormat()
{
	Clear();
}