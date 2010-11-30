#pragma once

class xEXPORT xVertexShader
{
	xHIDE_IMPLEMENTATION
	friend class xMaterial;	
	friend class xRenderDevice;	
public:
	xVertexShader(const xString& source);
	~xVertexShader();

	static xVertexShader* LoadFromFile(const xString& path);
};
