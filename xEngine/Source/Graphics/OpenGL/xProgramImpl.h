#pragma once

#include "xPrerequisites.h"

#include "../xBuffer.h"
#include "../xConstantBuffer.h"


struct xProgram::Impl
{
	struct UniformInfo
	{
		GLint				Location;
		GLenum				Type;
		GLint				Elements;
		size_t				Offset;
		xProgramVariable*	Variable;
	};

	typedef xArray<xConstantBuffer*>	BufferList;
	typedef xList<UniformInfo>	UniformInfoList;
	typedef xMap<xString, xProgramVariableHolder*>	VariableList;

	xSharedPtr<xVertexShader>	mVertexShader;	
	xSharedPtr<xPixelShader>	mFragmentShader;
	GLuint		mProgram;
	
	VariableList				mVariables;

	UniformInfoList				mUniforms;
	xBuffer*					mUniformsBuffer;

	BufferList					mBuffers;

	void SetupUniforms();	
};