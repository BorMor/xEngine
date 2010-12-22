#pragma once

#include "../xConstantBuffer.h"
#include "xPrerequisites.h"
#include "../xProgramVariable.h"

struct xProgram::Impl
{
	typedef xList<xConstantBuffer*>	BufferList;
	typedef xMap<xString, xProgramVariableHolder*>	VariableList;

	xSharedPtr<xVertexShader>	mVertexShader;
	xSharedPtr<xPixelShader>	mPixelShader;
	VariableList				mVariables;
	BufferList					mVSBuffers;	
	BufferList					mPSBuffers;		
	BufferList					mGSBuffers;


	void Reflect(ID3D10Blob* compiled_shader, BufferList& buffers);
};