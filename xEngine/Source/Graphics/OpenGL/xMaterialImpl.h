#pragma once

#include "xPrerequisites.h"

struct xMaterial::Impl
{
	xSharedPtr<xVertexShader>	mVertexShader;	
	xSharedPtr<xPixelShader>	mFragmentShader;	
	GLuint		mProgram;	
};