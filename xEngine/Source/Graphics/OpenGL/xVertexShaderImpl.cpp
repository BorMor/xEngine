#include "xEngine.h"
#include "xVertexShaderImpl.h"
#include "xShaderPreprocessor.h"

xVertexShader::xVertexShader(const xString& source)
{
	pImpl = new Impl;	
	pImpl->mName = glCreateShader(GL_VERTEX_SHADER);
	// Load and compile
	const char* ptr = source.c_str();
	glShaderSource(pImpl->mName, 1, (const char**)&ptr, 0);
	glCompileShader(pImpl->mName);
}

xVertexShader::~xVertexShader()
{
	glDeleteShader(pImpl->mName);
	xSAFE_DELETE(pImpl);
}

xVertexShader* xVertexShader::LoadFromFile(const xString& path)
{
	xString source = xShaderPreprocessor::LoadContents(path);
	return new xVertexShader(source);
}