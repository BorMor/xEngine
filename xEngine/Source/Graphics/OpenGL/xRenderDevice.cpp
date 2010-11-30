#include "xEngine.h"
#include "xPrerequisites.h"
#include "xMaterialImpl.h"
#include "xVertexBufferImpl.h"

#if defined(xPLATFORM_WIN32)

#include "Win32/xRenderWindowImpl.h"
// WGL_create_context
#define WGL_CONTEXT_DEBUG_BIT							0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT				0x0002
#define WGL_CONTEXT_MAJOR_VERSION						0x2091
#define WGL_CONTEXT_MINOR_VERSION						0x2092
#define WGL_CONTEXT_LAYER_PLANE							0x2093
#define WGL_CONTEXT_FLAGS								0x2094
#define ERROR_INVALID_VERSION							0x2095

typedef HGLRC (APIENTRYP PFNWGLCREATECONTEXTATTRIBSPROC)(HDC hDC, HGLRC hShareContext, const int *attribList);

#elif defined(xPLATFORM_LINUX)

extern "C" {
	typedef struct __GLXcontextRec *GLXContext;
	typedef XID GLXDrawable;
	extern XVisualInfo* glXChooseVisual( Display *dpy, int screen, int *attribList );
	extern GLXContext glXCreateContext( Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct );
	extern void glXDestroyContext( Display *dpy, GLXContext ctx );
	extern Bool glXMakeCurrent( Display *dpy, GLXDrawable drawable, GLXContext ctx);
}

#endif

struct xRenderDevice::Impl
{
	xMaterial*		mMaterial;
#if defined(xPLATFORM_WIN32)
	HGLRC			mRenderingContext;
#elif defined(xPLATFORM_LINUX)
	Display* mDisplay;
	GLXContext mGl;
#endif
};	

xRenderDevice::xRenderDevice(xRenderWindow* window)
{
	pImpl = new Impl();

#if defined(xPLATFORM_WIN32)
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
    
	int pf = ChoosePixelFormat(window->pImpl->mDeviceContext, &pfd);
	SetPixelFormat(window->pImpl->mDeviceContext, pf, &pfd);
	pImpl->mRenderingContext = wglCreateContext(window->pImpl->mDeviceContext);
	wglMakeCurrent(window->pImpl->mDeviceContext, pImpl->mRenderingContext);
	
	int attrs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION,	3,
		WGL_CONTEXT_MINOR_VERSION,	3,
		WGL_CONTEXT_FLAGS,			WGL_CONTEXT_FORWARD_COMPATIBLE_BIT,
		0
	};
	PFNWGLCREATECONTEXTATTRIBSPROC wglCreateContextAttribs = (PFNWGLCREATECONTEXTATTRIBSPROC)xOpenGL::GetProc("wglCreateContextAttribsARB");
	HGLRC hRC = wglCreateContextAttribs(window->pImpl->mDeviceContext, pImpl->mRenderingContext, attrs);
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(pImpl->mRenderingContext);
	pImpl->mRenderingContext = hRC;
	wglMakeCurrent(window->pImpl->mDeviceContext, pImpl->mRenderingContext);
	
	typedef BOOL (APIENTRY * PFNWGLSWAPINTERVALEXTPROC) (int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)xOpenGL::GetProc("wglSwapIntervalEXT");
	wglSwapIntervalEXT(0);
#elif defined(xPLATFORM_LINUX)
	pImpl->mDisplay = window->pImpl->mpDisplay;

	int att[] = { 4, 12, 24, 5, None };//{ GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };

	XVisualInfo* vi = glXChooseVisual(pImpl->mDisplay, DefaultScreen(pImpl->mDisplay), att);
	// TODO: Сделать проверку на NULL
	pImpl->mGl = glXCreateContext(pImpl->mDisplay, vi, 0, true);
	// TODO: Проверить на false
	glXMakeCurrent(pImpl->mDisplay, pImplwindow->pImpl->mWindow, pImpl->mGl);
#endif

	xOpenGL::Init();
	
	pImpl->mMaterial = 0;	
}

xRenderDevice::~xRenderDevice()
{
	xOpenGL::Shutdown();
#if defined(xPLATFORM_WIN32)
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(pImpl->mRenderingContext);	
#elif defined(xPLATFORM_LINUX)
	glXMakeCurrent(pImpl->mDisplay, None, NULL);
	glXDestroyContext(pImpl->mDisplay, pImpl->mGl);
#endif
	xSAFE_DELETE(pImpl);
}

void xRenderDevice::Clear(const xColor& color)
{
	glClearColor(color.R / 255.f, color.G / 255.f, color.B / 255.f, color.A / 255.f);
	//glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void xRenderDevice::SetMaterial(xMaterial* material)
{
	pImpl->mMaterial = material;
	if (pImpl->mMaterial)
		glUseProgram(pImpl->mMaterial->pImpl->mProgram);
	else
		glUseProgram(0);
}

void xRenderDevice::SetVertexBuffer(xVertexBuffer* buffer)
{
	glBindVertexArray(buffer->pImpl->mVAO);
}

void xRenderDevice::DrawPrimitive(xPrimitiveType::Enum type, xUInt32 start_vertex, xUInt32 vertex_count)
{
	GLenum mode = GL_POINTS;
	switch (type)
	{
	case xPrimitiveType::LineList:
		mode = GL_LINES;
		break;
	case xPrimitiveType::LineStrip:
		mode = GL_LINE_STRIP;
		break;					
	case xPrimitiveType::TriangleList:
		mode = GL_TRIANGLES;
		break;
	case xPrimitiveType::TriangleStrip:
		mode = GL_TRIANGLE_STRIP;
		break;
	}
	glDrawArrays(mode, start_vertex, vertex_count);
}

void xRenderDevice::Present()
{	
}

void xRenderDevice::SetUniform(const xString& name, const xMatrix& value)
{
	if (pImpl->mMaterial)
	{
		GLint location = glGetUniformLocation(pImpl->mMaterial->pImpl->mProgram, name.c_str());
		if (location != -1)
			glUniformMatrix4fv(location, 1, GL_FALSE, &value.M00);
	}
}