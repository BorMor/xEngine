#include "xEngine.h"
#include "xPrerequisites.h"
#include "xProgramImpl.h"
#include "xConstantBufferImpl.h"
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

	#include "Linux/xRenderWindowImpl.h"
	extern "C" {
	#define GLX_DOUBLEBUFFER	5
	#define GLX_RED_SIZE		8
	#define GLX_GREEN_SIZE		9
	#define GLX_BLUE_SIZE		10
	#define GLX_ALPHA_SIZE		11
	#define GLX_DEPTH_SIZE		12
	#define GLX_STENCIL_SIZE	13
	#define GLX_RENDER_TYPE			0x8011
	#define GLX_X_RENDERABLE		0x8012
	#define GLX_DRAWABLE_TYPE		0x8010
	#define GLX_WINDOW_BIT			0x00000001
	#define GLX_RGBA_BIT			0x00000001
	#define GLX_X_VISUAL_TYPE		0x22
	#define GLX_TRUE_COLOR			0x8002
	#define GLX_SAMPLE_BUFFERS              0x186a0 /*100000*/
	#define GLX_SAMPLES                     0x186a1 /*100001*/
	#define GLX_CONTEXT_FLAGS_ARB              0x2094
	#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
	#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
	#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092

	typedef struct __GLXcontextRec *GLXContext;
	typedef struct __GLXFBConfigRec *GLXFBConfig;
	typedef void (*__GLXextFuncPtr)(void);
	typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
	typedef struct {
	  Visual *visual;
	  VisualID visualid;
	  int screen;
	  int depth;
	  int c_class;
	  unsigned long red_mask;
	  unsigned long green_mask;
	  unsigned long blue_mask;
	  int colormap_size;
	  int bits_per_rgb;
	} XVisualInfo;

	extern __GLXextFuncPtr glXGetProcAddressARB(const GLubyte *);
	extern GLXFBConfig *glXChooseFBConfig(Display *dpy, int screen, const int *attribList, int *nitems);
	extern int glXGetFBConfigAttrib(Display *dpy, GLXFBConfig config, int attribute, int *value);
	extern XVisualInfo *glXGetVisualFromFBConfig(Display *dpy, GLXFBConfig config);
	extern void glXDestroyContext( Display *dpy, GLXContext ctx );
	extern Bool glXMakeCurrent(Display *dpy, XID drawable, GLXContext ctx);
	}
#endif

struct xRenderDevice::Impl
{
	xProgram*		mProgram;
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
	Window win = window->pImpl->mWindow;
	pImpl->mGl = 0;

	static int visual_attribs[] = {
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
		//GLX_SAMPLE_BUFFERS  , 1,
		//GLX_SAMPLES         , 4,
		None
	};

	int fbcount;
	GLXFBConfig *fbc = glXChooseFBConfig(pImpl->mDisplay, DefaultScreen(pImpl->mDisplay), visual_attribs, &fbcount);

	int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
	for (int i = 0; i < fbcount; i++){
		XVisualInfo *vi = glXGetVisualFromFBConfig(pImpl->mDisplay, fbc[i]);
		if (vi){
		  int samp_buf, samples;
		  glXGetFBConfigAttrib(pImpl->mDisplay, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
		  glXGetFBConfigAttrib(pImpl->mDisplay, fbc[i], GLX_SAMPLES       , &samples);
		  if (best_fbc < 0 || samp_buf && samples > best_num_samp)
			best_fbc = i, best_num_samp = samples;
		  if (worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
			worst_fbc = i, worst_num_samp = samples;
		}
		XFree(vi);
	}

	GLXFBConfig bestFbc = fbc[best_fbc];
	glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
	glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

    int context_attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
        GLX_CONTEXT_MINOR_VERSION_ARB, 3,
        GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        None
    };
    pImpl->mGl = glXCreateContextAttribsARB(pImpl->mDisplay, bestFbc, 0, True, context_attribs);
    glXMakeCurrent(pImpl->mDisplay, win, pImpl->mGl);
#endif

	xOpenGL::Init();
	
	pImpl->mProgram = 0;	
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

void xRenderDevice::SetProgram(xProgram* program)
{
	pImpl->mProgram = program;
	if (pImpl->mProgram)
	{
		xProgram::Impl* program_impl = pImpl->mProgram->pImpl;
		glUseProgram(program_impl->mProgram);
		program_impl->SetupUniforms();
		for (GLuint i = 0; i < program_impl->mBuffers.Size(); i++)
		{
			xConstantBuffer* buffer = program_impl->mBuffers[i];
			buffer->Flush();
			glBindBuffer(GL_UNIFORM_BUFFER, buffer->pImpl->mUBO);
		}
	}
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
}
