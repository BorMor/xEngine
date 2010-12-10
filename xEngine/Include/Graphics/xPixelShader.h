#pragma once

class xEXPORT xPixelShader
{
	xHIDE_IMPLEMENTATION
	friend class xGPUProgram;	
	friend class xRenderDevice;	
public:
	xPixelShader(const xString& source);
	~xPixelShader();

	static xPixelShader* LoadFromFile(const xString& path);
};
