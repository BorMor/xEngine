#pragma once

struct xShaderType
{
	enum Enum
	{
		Vertex,
		Fragment,
		Geometry
	};
};

class xEXPORT xShader
{
	xHIDE_IMPLEMENTATION
	friend class xMaterial;	
public:
	xShader(xShaderType::Enum type);
	~xShader();

	void LoadFromFile(const xString& path);
};

typedef xSharedPtr<xShader> xShaderPtr;
