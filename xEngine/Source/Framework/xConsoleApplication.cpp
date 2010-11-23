#include "xEngine.h"

xConsoleApplication::xConsoleApplication()
{
	mConsole = new xConsole();
}

xConsoleApplication::~xConsoleApplication()
{
	xSAFE_DELETE(mConsole);
}

bool xConsoleApplication::Initialize()
{
    return OnInit();
}

void xConsoleApplication::Shutdown()
{
    OnShutdown();
}
