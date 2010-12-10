#include "xEngine.h"
#include "xVertexShaderImpl.h"

xVertexShader::xVertexShader(const xString& source)
{
	pImpl = new Impl;
	ID3D10Blob*	msgs = 0;
	D3D10CompileShader(source.c_str(), source.Length(), 0, 0, 0, "main", "vs_4_0", 0, &pImpl->mCompiledShader, &msgs);	//4_1??

	gDevice->CreateVertexShader(pImpl->mCompiledShader->GetBufferPointer(), pImpl->mCompiledShader->GetBufferSize(), &pImpl->mShader);
	D3D10ReflectShader(pImpl->mCompiledShader->GetBufferPointer(), pImpl->mCompiledShader->GetBufferSize(), &pImpl->mReflection);
}

xVertexShader::~xVertexShader()
{
	if (pImpl->mCompiledShader)
		pImpl->mCompiledShader->Release();
	if (pImpl->mShader)
		pImpl->mShader->Release();
	xSAFE_DELETE(pImpl);
}

xVertexShader* xVertexShader::LoadFromFile(const xString& path)
{
	xString source = xFile::ReadToString(path);
	return new xVertexShader(source);
}