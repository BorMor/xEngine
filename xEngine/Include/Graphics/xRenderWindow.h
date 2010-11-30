#pragma once

class xEXPORT xRenderWindow
{
	xHIDE_IMPLEMENTATION
	friend class xRenderDevice;
public:
	xRenderWindow(xUInt32 width, xUInt32 height);
	~xRenderWindow();

	void Show();
	void Hide();
	void ProcessMessages();
	bool IsClosed() const;
	xUInt32 Handle() const;
	void Present();
protected:
	xUInt32 mWidth;
	xUInt32 mHeight;
};
