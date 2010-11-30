#pragma once

#include "../xPrerequisites.h"

struct xRenderWindow::Impl
{
	WNDCLASSEX  mWindowClass;
	HWND        mHandle;
	HDC			mDeviceContext;
	bool		mClosed;
};