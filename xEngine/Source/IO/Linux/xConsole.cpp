#include "xEngine.h"
#include <stdlib.h>

struct xConsole::Impl
{
};

xConsole::xConsole()
    : pImpl(0)
{
}

xConsole::~xConsole()
{
}

void xConsole::SetTitle(const xString& title)
{
}

void xConsole::Print(const xString& text, xConsoleColor::Enum color)
{
	switch (color)
	{
    case xConsoleColor::Black:
        printf("\033[22;30m");
	    break;
    case xConsoleColor::Red:
        printf("\033[22;31m");
	    break;
    case xConsoleColor::Green:
        printf("\033[22;32m");
	    break;
    case xConsoleColor::Yellow:
        printf("\033[22;33m");
	    break;
    case xConsoleColor::Blue:
        printf("\033[22;34m");
	    break;
    case xConsoleColor::Purple:
        printf("\033[22;35m");
	    break;
    case xConsoleColor::Cyan:
        printf("\033[22;36m");
	    break;
    case xConsoleColor::White:
        printf("\033[22;37m");
	    break;
	}
    printf("%s", text.c_str());
    printf("\033[22;37m");
}

xString xConsole::Read()
{
    return "";
}
