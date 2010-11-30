#include "xEngine.h"
#include "xRenderWindowImpl.h"

LRESULT WINAPI WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

xRenderWindow::xRenderWindow(xUInt32 width, xUInt32 height)
	: mWidth(width), mHeight(height)
{
	pImpl = new Impl;
	
	pImpl->mClosed = false;

	pImpl->mWindowClass.cbSize = sizeof(WNDCLASSEX);
    pImpl->mWindowClass.style = CS_CLASSDC;
    pImpl->mWindowClass.lpfnWndProc = WindowProc;
    pImpl->mWindowClass.cbClsExtra = 0;
    pImpl->mWindowClass.cbWndExtra = 0;
    pImpl->mWindowClass.hInstance = GetModuleHandle(NULL);
    pImpl->mWindowClass.hIcon = NULL;
    pImpl->mWindowClass.hCursor = NULL;
    pImpl->mWindowClass.hbrBackground = NULL;
    pImpl->mWindowClass.lpszMenuName = NULL;
    pImpl->mWindowClass.lpszClassName = "xWindow";
    pImpl->mWindowClass.hIconSm = NULL;

    RegisterClassEx(&pImpl->mWindowClass);

    pImpl->mHandle = CreateWindow("xWindow", "xEngine",
							WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, width, height,
							NULL, NULL, pImpl->mWindowClass.hInstance, NULL);    

	pImpl->mSwapChain = 0;
	if (gDevice)
		pImpl->Init();	
}

xRenderWindow::~xRenderWindow()
{
	if (pImpl->mRenderTargetView)
		pImpl->mRenderTargetView->Release();

    if (pImpl->mSwapChain)
		pImpl->mSwapChain->Release();

	UnregisterClass("xWindow", pImpl->mWindowClass.hInstance);
	xSAFE_DELETE(pImpl);
}

void xRenderWindow::Show()
{
	ShowWindow(pImpl->mHandle, SW_SHOWDEFAULT);
	UpdateWindow(pImpl->mHandle);
}

void xRenderWindow::Hide()
{
	ShowWindow(pImpl->mHandle, SW_HIDE);
}

void xRenderWindow::ProcessMessages()
{
    MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
    while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
			pImpl->mClosed = true;
    }
}

bool xRenderWindow::IsClosed() const
{
	return pImpl->mClosed;
}

xUInt32 xRenderWindow::Handle() const
{
	return (xUInt32)pImpl->mHandle;
}

void xRenderWindow::Present()
{
	if (pImpl->mSwapChain)
		pImpl->mSwapChain->Present(0, 0);
}