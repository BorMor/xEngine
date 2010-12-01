#pragma once

#include "../xPrerequisites.h"

struct xRenderWindow::Impl{
	Display* mpDisplay;
	Window mWindow;
	bool mClosed;
	Atom mWmDeleteWindow;
};
