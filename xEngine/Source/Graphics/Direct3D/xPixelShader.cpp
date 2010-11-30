#include "xEngine.h"
#include "xPixelShaderImpl.h"

xPixelShader::xPixelShader(const xString& source)
{
	pImpl = new Impl;
	ID3D10Blob*	blob = 0;
	ID3D10Blob*	msgs = 0;
	D3D10CompileShader(source.c_str(), source.Length(), 0, 0, 0, "main", "ps_4_0", 0, &blob, &msgs);	//4_1??

	gDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), &pImpl->mShader);
	D3D10ReflectShader(blob->GetBufferPointer(), blob->GetBufferSize(), &pImpl->mReflection);
	blob->Release();	
}

xPixelShader::~xPixelShader()
{
	if (pImpl->mShader)
		pImpl->mShader->Release();
	xSAFE_DELETE(pImpl);
}

xPixelShader* xPixelShader::LoadFromFile(const xString& path)
{
	xString source = xFile::ReadToString(path);
	return new xPixelShader(source);
}