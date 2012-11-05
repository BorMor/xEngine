#pragma once

#include "xPrerequisites.h"

struct xPixelShader::Impl
{
	ID3D11PixelShader*		mShader;
	ID3DBlob*				mCompiledShader;
};