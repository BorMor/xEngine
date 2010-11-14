#pragma once
#include "xPrerequisites.h"

struct xMaterial::Impl
{
	//bool	mVertexShaderChanged;
	GLuint	mVertexShader;	
	//bool	mFragmentShaderChanged;
	GLuint	mFragmentShader;	
	GLuint	mProgram;
	
};