#pragma once

class xEXPORT xConsole
{
	xHIDE_IMPLEMENTATION
public:
	xConsole();
	~xConsole();

	void SetTitle(const xString& title);
	void Print(const xString& text, xColor color = xColor::WHITE);
	xString Read();
};