#pragma once

#include "xPrerequisites.h"

struct xVertexShader::Impl
{
	ID3D11VertexShader*		mShader;
	ID3DBlob*				mCompiledShader;	
};