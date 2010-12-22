#pragma once

class xEXPORT xProgram
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;	
public:
	xProgram(const xString& vertex_shader, const xString& pixel_shader, const xString& geometry_shader = "");
	~xProgram();

	xProgramVariableHolder* GetVariableByName(const xString& name);
};

typedef xSharedPtr<xProgram> xProgramPtr;
