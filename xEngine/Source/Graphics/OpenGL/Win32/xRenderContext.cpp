#include "xEngine.h"
#include "../xPrerequisites.h"
#include "../xRenderContext.h"

// WGL_create_context
#define WGL_CONTEXT_DEBUG_BIT							0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT				0x0002
#define WGL_CONTEXT_MAJOR_VERSION						0x2091
#define WGL_CONTEXT_MINOR_VERSION						0x2092
#define WGL_CONTEXT_LAYER_PLANE							0x2093
#define WGL_CONTEXT_FLAGS								0x2094
#define ERROR_INVALID_VERSION							0x2095

typedef HGLRC (APIENTRYP PFNWGLCREATECONTEXTATTRIBSPROC)(HDC hDC, HGLRC hShareContext, const int *attribList);

struct xRenderContext::Impl
{
	HWND	mHandle;
	HGLRC	mRenderingContext;
	HDC		mDeviceContext;
};

xRenderContext::xRenderContext(xRenderWindow* window)
{
	pImpl = new Impl();

	pImpl->mHandle = (HWND)window->Handle();
	static	PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        16,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        16,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    pImpl->mDeviceContext = GetDC(pImpl->mHandle);
	int pf = ChoosePixelFormat(pImpl->mDeviceContext, &pfd);
	SetPixelFormat(pImpl->mDeviceContext, pf, &pfd);
	pImpl->mRenderingContext = wglCreateContext(pImpl->mDeviceContext);
	wglMakeCurrent(pImpl->mDeviceContext, pImpl->mRenderingContext);

	int attrs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION,	3,
		WGL_CONTEXT_MINOR_VERSION,	2,
		WGL_CONTEXT_FLAGS,			WGL_CONTEXT_FORWARD_COMPATIBLE_BIT,
		0
	};	
	PFNWGLCREATECONTEXTATTRIBSPROC wglCreateContextAttribs = (PFNWGLCREATECONTEXTATTRIBSPROC)xOpenGL::GetProc("wglCreateContextAttribsARB");
	HGLRC hRC = wglCreateContextAttribs(pImpl->mDeviceContext, pImpl->mRenderingContext, attrs);
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(pImpl->mRenderingContext);
	pImpl->mRenderingContext = hRC;
	wglMakeCurrent(pImpl->mDeviceContext, pImpl->mRenderingContext);
	
	typedef BOOL (APIENTRY * PFNWGLSWAPINTERVALEXTPROC) (int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)xOpenGL::GetProc("wglSwapIntervalEXT");
	wglSwapIntervalEXT(0);
}

xRenderContext::~xRenderContext()
{
	wglMakeCurrent(pImpl->mDeviceContext, NULL);
	wglDeleteContext(pImpl->mRenderingContext);
	ReleaseDC(pImpl->mHandle, pImpl->mDeviceContext);

	xSAFE_DELETE(pImpl);
}

void xRenderContext::SwapBuffers()
{
	::SwapBuffers(pImpl->mDeviceContext);
}