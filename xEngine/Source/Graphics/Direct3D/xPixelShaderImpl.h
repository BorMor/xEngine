#pragma once

#include "xPrerequisites.h"

struct xPixelShader::Impl
{
	ID3D10PixelShader*		mShader;
	ID3D10Blob*				mCompiledShader;
};