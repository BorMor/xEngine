#include "xEngine.h"
#include "xPixelShaderImpl.h"
#include "xShaderPreprocessor.h"

xPixelShader::xPixelShader(const xString& source)
{
	pImpl = new Impl;	
	pImpl->mName = glCreateShader(GL_FRAGMENT_SHADER);
	// Load and compile
	const char* ptr = source.c_str();
	glShaderSource(pImpl->mName, 1, (const char**)&ptr, 0);
	glCompileShader(pImpl->mName);
}

xPixelShader::~xPixelShader()
{
	glDeleteShader(pImpl->mName);
	xSAFE_DELETE(pImpl);
}

xPixelShader* xPixelShader::LoadFromFile(const xString& path)
{
	xString source = xShaderPreprocessor::LoadContents(path);
	return new xPixelShader(source);
}