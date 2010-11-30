#pragma once

#include "xPrerequisites.h"

struct xVertexShader::Impl
{
	ID3D10VertexShader*		mShader;
	ID3D10Blob*				mCompiledShader;
	ID3D10ShaderReflection*	mReflection;
};