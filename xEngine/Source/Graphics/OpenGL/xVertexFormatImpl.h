#pragma once
#include "xPrerequisites.h"

struct xVertexFormat::Impl
{
	struct Element
	{
		size_t						Offset;
		xVertexElementType::Enum	Type;
		xVertexElementUsage::Enum	Usage;
	};
	typedef xList<Element> ElementList;

	ElementList		mElements;
};