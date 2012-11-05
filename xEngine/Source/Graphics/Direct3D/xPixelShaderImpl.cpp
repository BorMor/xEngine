#include "xEngine.h"
#include "xPixelShaderImpl.h"

xPixelShader::xPixelShader(const xString& source)
{
	pImpl = new Impl;
	ID3DBlob*	msgs = 0;
	HRESULT hr = D3DCompile(source.c_str(), source.Length(), "none", NULL, NULL, "main", "ps_5_0", 0, D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS, &pImpl->mCompiledShader, &msgs );
	if (msgs)
		OutputDebugString((char*)msgs->GetBufferPointer());
	gDevice->CreatePixelShader(pImpl->mCompiledShader->GetBufferPointer(), pImpl->mCompiledShader->GetBufferSize(), NULL, &pImpl->mShader);
}

xPixelShader::~xPixelShader()
{
	if (pImpl->mCompiledShader)
		pImpl->mCompiledShader->Release();
	if (pImpl->mShader)
		pImpl->mShader->Release();
	xSAFE_DELETE(pImpl);
}

xPixelShader* xPixelShader::LoadFromFile(const xString& path)
{
	xString source = xFile::ReadToString(path);
	return new xPixelShader(source);
}