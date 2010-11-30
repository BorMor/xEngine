#include "xEngine.h"
#include "xMaterialImpl.h"
#include "xVertexShaderImpl.h"
#include "xPixelShaderImpl.h"

xMaterial::xMaterial()
{
	pImpl = new Impl;

	pImpl->mProgram = glCreateProgram();   
}

xMaterial::~xMaterial()
{	
	glDeleteProgram(pImpl->mProgram);
	if (pImpl->mFragmentShader)
		glDeleteShader(pImpl->mFragmentShader);
	if (pImpl->mVertexShader)
		glDeleteShader(pImpl->mVertexShader);
	xSAFE_DELETE(pImpl);
}

void xMaterial::SetVertexShader(const xString& path)
{
	pImpl->mVertexShader = xVertexShader::LoadFromFile(path);
	glAttachShader(pImpl->mProgram, pImpl->mVertexShader->pImpl->mName);	
	
	glLinkProgram(pImpl->mProgram);
}

void xMaterial::SetFragmentShader(const xString& path)
{
	pImpl->mFragmentShader = xPixelShader::LoadFromFile(path);
	glAttachShader(pImpl->mProgram, pImpl->mFragmentShader->pImpl->mName);

	glLinkProgram(pImpl->mProgram);
}