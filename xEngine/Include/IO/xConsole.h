#pragma once

struct xConsoleColor
{
    enum Enum
    {
         Black,
         Red,
         Green,
         Yellow,
         Blue,
         Purple,
         Cyan,
         White
    };
};

class xEXPORT xConsole
{
	xHIDE_IMPLEMENTATION
public:
	xConsole();
	~xConsole();

	void SetTitle(const xString& title);
	void Print(const xString& text, xConsoleColor::Enum color = xConsoleColor::White);
	xString Read();
};
