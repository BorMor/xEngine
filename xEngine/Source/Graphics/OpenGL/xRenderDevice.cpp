#include "xEngine.h"
#include "xPrerequisites.h"
#include "xMaterialImpl.h"
#include "xVertexBufferImpl.h"

// WGL_create_context
#define WGL_CONTEXT_DEBUG_BIT							0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT				0x0002
#define WGL_CONTEXT_MAJOR_VERSION						0x2091
#define WGL_CONTEXT_MINOR_VERSION						0x2092
#define WGL_CONTEXT_LAYER_PLANE							0x2093
#define WGL_CONTEXT_FLAGS								0x2094
#define ERROR_INVALID_VERSION							0x2095

typedef HGLRC (APIENTRYP PFNWGLCREATECONTEXTATTRIBSPROC)(HDC hDC, HGLRC hShareContext, const int *attribList);

struct xRenderDevice::Impl
{
#if defined(xPLATFORM_WIN32)
	HWND	mHandle;
#else
#error 1
#endif
	HGLRC	mRenderingContext;
	HDC		mDeviceContext;

	xMaterial*		mMaterial;
	bool			mVertexFormatChanged;
	xVertexFormat*	mVertexFormat;
};	

xRenderDevice::xRenderDevice(xRenderWindow* window)
{
	pImpl = new Impl();
#if defined(xPLATFORM_WIN32)
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
#else
	#error 1
#endif
	
	typedef BOOL (APIENTRY * PFNWGLSWAPINTERVALEXTPROC) (int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)xOpenGL::GetProc("wglSwapIntervalEXT");
	wglSwapIntervalEXT(0);

	xOpenGL::Init();
	
	pImpl->mMaterial = 0;
	pImpl->mVertexFormatChanged = false;
	pImpl->mVertexFormat = 0;	
}

xRenderDevice::~xRenderDevice()
{
	xOpenGL::Shutdown();

	wglMakeCurrent(pImpl->mDeviceContext, NULL);
	wglDeleteContext(pImpl->mRenderingContext);
	ReleaseDC(pImpl->mHandle, pImpl->mDeviceContext);

	xSAFE_DELETE(pImpl);
}

void xRenderDevice::Clear(const xColor& color)
{
	glClearColor(color.R / 255.f, color.G / 255.f, color.B / 255.f, color.A / 255.f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void xRenderDevice::SetMaterial(xMaterial* material)
{
	if (pImpl->mMaterial)
		glUseProgram(pImpl->mMaterial->pImpl->mProgram);
	else
		glUseProgram(0);
	pImpl->mMaterial = material;
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
#if defined(xPLATFORM_WIN32)
	SwapBuffers(pImpl->mDeviceContext);
#else
#error 1
#endif
}