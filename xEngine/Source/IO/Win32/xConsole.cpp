#include "xEngine.h"

#if defined(xPLATFORM_WIN32)

struct xConsole::Impl
{
	HANDLE mHandle;
};

xConsole::xConsole()
{
	pImpl = new Impl;
	AllocConsole();
	pImpl->mHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[1024];
	GetConsoleTitle(buf, 1024);
	HWND hwnd = FindWindow("ConsoleWindowClass", buf);
	HMENU hm = GetSystemMenu(hwnd, FALSE);
	DeleteMenu(hm, SC_CLOSE , MF_BYCOMMAND);
	DrawMenuBar(hwnd);
}

xConsole::~xConsole()
{
	FreeConsole();
	xSAFE_DELETE(pImpl);
}

void xConsole::SetTitle(const xString& title)
{
	SetConsoleTitle(title.c_str());
}

void xConsole::Print(const xString& text, xColor color)
{
	WORD attrs = FOREGROUND_INTENSITY;
	if (color.R >= 128)
		attrs |= FOREGROUND_RED;
	if (color.G >= 128)
		attrs |= FOREGROUND_GREEN;
	if (color.B >= 128)
		attrs |= FOREGROUND_BLUE;
	SetConsoleTextAttribute(pImpl->mHandle, attrs);
	DWORD written;
	WriteConsole(pImpl->mHandle, text.c_str(), (DWORD)text.Length(), &written, NULL);
	SetConsoleTextAttribute(pImpl->mHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

xString xConsole::Read()
{
	static char buf[1024];
	DWORD readed;
	ReadConsole(GetStdHandle(STD_INPUT_HANDLE), buf, 1024, &readed, 0);
	return xString(buf);
}
#endif
