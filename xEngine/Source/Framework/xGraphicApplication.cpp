#include "xEngine.h"

xGraphicApplication::xGraphicApplication()
{    
}

xGraphicApplication::~xGraphicApplication()
{	
}

bool xGraphicApplication::Initialize()
{	
	mRenderWindow = new xRenderWindow(800, 600);
	mRenderDevice = new xRenderDevice(mRenderWindow);
	mRenderWindow->Show();
    if (!OnInit())
		return false;
	mTimer = new xTimer();
	return true;
}

void xGraphicApplication::Run()
{
	while (true)
	{
		mRenderWindow->ProcessMessages();
		if (mRenderWindow->IsClosed())
			break;
		float dt = mTimer->ElapsedTime();
		mTimer->Reset();
		OnUpdate(dt);
	}
}

void xGraphicApplication::Shutdown()
{
	xSAFE_DELETE(mTimer);
    OnShutdown();
	xSAFE_DELETE(mRenderDevice);
	xSAFE_DELETE(mRenderWindow);
}
