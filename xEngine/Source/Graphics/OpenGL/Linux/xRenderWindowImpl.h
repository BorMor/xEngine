#pragma once

struct xRenderWindow::Impl{
	Display* mpDisplay;
	Window mWindow;
	bool mClosed;
	Atom mWmDeleteWindow;
};
