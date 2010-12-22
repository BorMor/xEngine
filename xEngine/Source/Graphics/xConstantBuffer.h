#pragma once

#include "xBuffer.h"

class xConstantBuffer : public xBuffer
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;	
	friend class xProgram;	
public:
	xConstantBuffer(size_t size_in_bytes);
	~xConstantBuffer();

	void Flush();
};
