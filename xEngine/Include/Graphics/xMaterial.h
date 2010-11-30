#pragma once

class xEXPORT xMaterial
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;	
public:
	xMaterial();
	~xMaterial();

	void SetVertexShader(const xString& source);
	void SetFragmentShader(const xString& source);
};

typedef xSharedPtr<xMaterial> xMaterialPtr;
