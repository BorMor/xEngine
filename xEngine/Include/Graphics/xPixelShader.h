#pragma once

class xEXPORT xPixelShader
{
	xHIDE_IMPLEMENTATION
	friend class xProgram;	
	friend class xRenderDevice;	
public:
	xPixelShader(const xString& source);
	~xPixelShader();

	static xPixelShader* LoadFromFile(const xString& path);
};
