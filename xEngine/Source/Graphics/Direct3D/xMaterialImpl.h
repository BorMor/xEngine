#pragma once

#include "xPrerequisites.h"

struct xMaterial::Impl
{
	xSharedPtr<xVertexShader>	mVertexShader;
	xSharedPtr<xPixelShader>	mPixelShader;
	//xShaderPtr	mFragmentShader;	
//	GLuint		mProgram;	
};