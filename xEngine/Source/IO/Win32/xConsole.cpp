#include "xEngine.h"

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

void xConsole::Print(const xString& text, xConsoleColor::Enum color)
{
	WORD attrs = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	switch (color)
	{
    case xConsoleColor::Black:
        attrs = 0;
	    break;
    case xConsoleColor::Red:
        attrs = 4;
	    break;
    case xConsoleColor::Green:
        attrs = 2;
	    break;
    case xConsoleColor::Yellow:
        attrs = 6;
	    break;
    case xConsoleColor::Blue:
        attrs = 1;
	    break;
    case xConsoleColor::Purple:
        attrs = 5;
	    break;
    case xConsoleColor::Cyan:
        attrs = 3;
	    break;
    case xConsoleColor::White:
        attrs = 7;
	    break;
	}
	SetConsoleTextAttribute(pImpl->mHandle, attrs | FOREGROUND_INTENSITY);
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
