#pragma once

#include "xPrerequisites.h"

struct xMaterial::Impl
{
	xShaderPtr	mVertexShader;	
	xShaderPtr	mFragmentShader;	
	GLuint		mProgram;	
};