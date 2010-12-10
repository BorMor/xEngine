#include "xEngine.h"
#include "xGPUProgramImpl.h"
#include "xVertexShaderImpl.h"
#include "xPixelShaderImpl.h"

xGPUProgram::xGPUProgram(const xString& vertex_shader, const xString& pixel_shader, const xString& geometry_shader)
{
	pImpl = new Impl;

	pImpl->mProgram = glCreateProgram();  
	
	pImpl->mVertexShader = xVertexShader::LoadFromFile(vertex_shader);
	glAttachShader(pImpl->mProgram, pImpl->mVertexShader->pImpl->mName);	

	pImpl->mFragmentShader = xPixelShader::LoadFromFile(pixel_shader);
	glAttachShader(pImpl->mProgram, pImpl->mFragmentShader->pImpl->mName);

	glLinkProgram(pImpl->mProgram);
}

xGPUProgram::~xGPUProgram()
{	
	glDeleteProgram(pImpl->mProgram);
	if (pImpl->mFragmentShader)
		glDeleteShader(pImpl->mFragmentShader);
	if (pImpl->mVertexShader)
		glDeleteShader(pImpl->mVertexShader);
	xSAFE_DELETE(pImpl);
}