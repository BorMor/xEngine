#include "xEngine.h"
#include "xPixelShaderImpl.h"

xPixelShader::xPixelShader(const xString& source)
{
	pImpl = new Impl;
	ID3D10Blob*	msgs = 0;
	D3D10CompileShader(source.c_str(), source.Length(), 0, 0, 0, "main", "ps_4_0", 0, &pImpl->mCompiledShader, &msgs);	//4_1??
	if (msgs)
		OutputDebugString((char*)msgs->GetBufferPointer());
	gDevice->CreatePixelShader(pImpl->mCompiledShader->GetBufferPointer(), pImpl->mCompiledShader->GetBufferSize(), &pImpl->mShader);
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