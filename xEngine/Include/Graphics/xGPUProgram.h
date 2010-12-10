#pragma once

class xEXPORT xGPUProgram
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;
public:
	xGPUProgram(const xString& vertex_shader, const xString& pixel_shader, const xString& geometry_shader = "");
	~xGPUProgram();

	//static xGPUProgram* LoadFromFile();
};

typedef xSharedPtr<xGPUProgram> xxGPUProgramPtr;
