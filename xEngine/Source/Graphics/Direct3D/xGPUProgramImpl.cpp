#include "xEngine.h"
#include "xGPUProgramImpl.h"

xGPUProgram::xGPUProgram(const xString& vertex_shader, const xString& pixel_shader, const xString& geometry_shader)
{
	pImpl = new Impl;
	pImpl->mVertexShader = xVertexShader::LoadFromFile(vertex_shader);
	pImpl->mPixelShader = xPixelShader::LoadFromFile(pixel_shader);
}

xGPUProgram::~xGPUProgram()
{
	xSAFE_DELETE(pImpl);
}