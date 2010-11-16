#pragma once

class xEXPORT xMaterial
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;	
public:
	xMaterial();
	~xMaterial();

	void SetVertexShader(const xString& path);
	void SetFragmentShader(const xString& path);
};

typedef xSharedPtr<xMaterial> xMaterialPtr;
