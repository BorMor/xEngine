#include "xEngine.h"
#include "xMaterialImpl.h"
#include "xVertexShaderImpl.h"

xMaterial::xMaterial()
{
	pImpl = new Impl;

	//pImpl->mVertexShader = new xShader(xShaderType::Vertex);
	//pImpl->mFragmentShader = new xShader(xShaderType::Fragment);

/*	pImpl->mProgram = glCreateProgram();
	glAttachShader(pImpl->mProgram, pImpl->mVertexShader->pImpl->mName);	
    glAttachShader(pImpl->mProgram, pImpl->mFragmentShader->pImpl->mName);
	glLinkProgram(pImpl->mProgram);*/
}

xMaterial::~xMaterial()
{
	/*glDeleteProgram(pImpl->mProgram);
	glDeleteShader(pImpl->mFragmentShader);
	glDeleteShader(pImpl->mVertexShader);*/
	xSAFE_DELETE(pImpl);
}

void xMaterial::SetVertexShader(const xString& path)
{
	pImpl->mVertexShader = xVertexShader::LoadFromFile(path);
}

void xMaterial::SetFragmentShader(const xString& path)
{
	pImpl->mPixelShader = xPixelShader::LoadFromFile(path);
}