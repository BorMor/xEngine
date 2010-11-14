#pragma once

class xRenderWindow
{
	xHIDE_IMPLEMENTATION
public:
	xRenderWindow(xUInt32 width, xUInt32 height);
	~xRenderWindow();

	void Show();
	void Hide();
	void ProcessMessages();
	bool IsClosed() const;
	xUInt32 Handle() const;
protected:
	xUInt32 mWidth;
	xUInt32 mHeight;
};
