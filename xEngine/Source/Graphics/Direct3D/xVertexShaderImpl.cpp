#include "xEngine.h"
#include "xVertexShaderImpl.h"

xVertexShader::xVertexShader(const xString& source)
{
	pImpl = new Impl;
	ID3DBlob*	msgs = 0;
	HRESULT hr = D3DCompile(source.c_str(), source.Length(), "none", NULL, NULL, "main", "vs_5_0", 0, D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS, &pImpl->mCompiledShader, &msgs );
	gDevice->CreateVertexShader(pImpl->mCompiledShader->GetBufferPointer(), pImpl->mCompiledShader->GetBufferSize(), NULL, &pImpl->mShader);
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