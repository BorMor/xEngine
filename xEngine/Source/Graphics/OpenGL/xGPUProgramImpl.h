#pragma once

#include "xPrerequisites.h"

struct xGPUProgram::Impl
{
	xSharedPtr<xVertexShader>	mVertexShader;	
	xSharedPtr<xPixelShader>	mFragmentShader;	
	GLuint		mProgram;	
};