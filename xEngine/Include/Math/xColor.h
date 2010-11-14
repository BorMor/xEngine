#pragma once

class xEXPORT xColor
{
public:
	xColor();
	xColor(xByte r, xByte g, xByte b, xByte a = 255);

	xByte R;
	xByte G;
	xByte B;
	xByte A;

	xUInt32 ARGB() const;
	xUInt32 RGBA() const;

	static const xColor WHITE;
	static const xColor RED;
	static const xColor GREEN;
	static const xColor BLUE;
	static const xColor MAGENTA;
	static const xColor CYAN;
	static const xColor YELLOW;
	static const xColor BLACK;
};

#include "xColor.inl"
