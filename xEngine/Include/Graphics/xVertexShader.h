#pragma once

class xEXPORT xVertexShader
{
	xHIDE_IMPLEMENTATION
	friend class xGPUProgram;	
	friend class xRenderDevice;	
public:
	xVertexShader(const xString& source);
	~xVertexShader();

	static xVertexShader* LoadFromFile(const xString& path);
};
