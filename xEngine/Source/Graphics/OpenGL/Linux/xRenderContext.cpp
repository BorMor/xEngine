#include "xEngine.h"
#include "../xPrerequisites.h"
#include "../xRenderContext.h"


extern "C" {
	typedef struct __GLXcontextRec *GLXContext;
	typedef XID GLXDrawable;
	extern XVisualInfo* glXChooseVisual( Display *dpy, int screen, int *attribList );
	extern GLXContext glXCreateContext( Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct );
	extern void glXDestroyContext( Display *dpy, GLXContext ctx );
	extern Bool glXMakeCurrent( Display *dpy, GLXDrawable drawable, GLXContext ctx);
	extern void glXSwapBuffers( Display *dpy, GLXDrawable drawable );
}

struct xRenderContext::Impl
{
	Window mWindow;
	Display* mDisplay;
	GLXContext mGl;
};

xRenderContext::xRenderContext(xRenderWindow* window){
	pImpl = new Impl;
	pImpl->mDisplay = window->pImpl->mpDisplay;
	pImpl->mWindow = window->pImpl->mWindow;

	int att[] = { 4, 12, 24, 5, None };//{ GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

	XVisualInfo* vi = glXChooseVisual(pImpl->mDisplay, DefaultScreen(pImpl->mDisplay), att);
	// TODO: Сделать проверку на NULL
	pImpl->mGl = glXCreateContext(pImpl->mDisplay, vi, 0, true);
	// TODO: Проверить на false
	glXMakeCurrent(pImpl->mDisplay, pImpl->mWindow, pImpl->mGl);
}

xRenderContext::~xRenderContext(){
	glXMakeCurrent(pImpl->mDisplay, None, NULL);
	glXDestroyContext(pImpl->mDisplay, pImpl->mGl);
	xSAFE_DELETE(pImpl);
}

void xRenderContext::SwapBuffers(){
	glXSwapBuffers(pImpl->mDisplay, pImpl->mWindow);
}
