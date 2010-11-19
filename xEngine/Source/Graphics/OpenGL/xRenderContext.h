#pragma once

class xRenderContext
{
	xHIDE_IMPLEMENTATION
public:
	xRenderContext(xRenderWindow* window);
	~xRenderContext();

	void SwapBuffers();
};