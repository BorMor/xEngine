#pragma once

class xEXPORT xTimer
{
	xHIDE_IMPLEMENTATION
public:
	xTimer();
	~xTimer();

	void Reset();
	float ElapsedTime();
};