#include "xEngine.h"
#include "xPrerequisites.h"
#include "xProgramImpl.h"
#include "xConstantBufferImpl.h"
#include "xIndexBufferImpl.h"
#include "xVertexBufferImpl.h"
#include "xTextureImpl.h"

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
	xVertexBuffer*	mVertexBuffer;
	bool			mVertexBufferChanged;
	xIndexBuffer*	mIndexBuffer;
	bool			mIndexBufferChanged;

	void BindNecessaryData()
	{
		if (mVertexBufferChanged)
		{
			glBindVertexArray(mVertexBuffer->pImpl->mVAO);
			mVertexBufferChanged = false;
		}
		if (mIndexBufferChanged)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer->pImpl->mIBO);
			mIndexBufferChanged = false;
		}
		if (mProgram)
		{
			xProgram::Impl* program_impl = mProgram->pImpl;
			const xByte* data = program_impl->mUniformsBuffer ? (const xByte*)program_impl->mUniformsBuffer->Data() : NULL;
			for (xProgram::Impl::UniformInfoList::Iterator it = program_impl->mUniforms.Begin(); it != program_impl->mUniforms.End(); ++it)
			{
				switch (it->Type)
				{
				case GL_FLOAT_VEC2:
					glUniform2fv(it->Location, it->Elements, (const GLfloat*)(data + it->Offset));
					break;
				case GL_FLOAT_VEC3:
					glUniform3fv(it->Location, it->Elements, (const GLfloat*)(data + it->Offset));
					break;
				case GL_FLOAT_VEC4:
					glUniform4fv(it->Location, it->Elements, (const GLfloat*)(data + it->Offset));
					break;
				case GL_INT_VEC2:
					glUniform2iv(it->Location, it->Elements, (const GLint*)(data + it->Offset));
					break;
				case GL_INT_VEC3:
					glUniform3iv(it->Location, it->Elements, (const GLint*)(data + it->Offset));
					break;
				case GL_INT_VEC4:
					glUniform4iv(it->Location, it->Elements, (const GLint*)(data + it->Offset));
					break;
				case GL_FLOAT_MAT4:
					glUniformMatrix4fv(it->Location, it->Elements, GL_TRUE, (const GLfloat*)(data + it->Offset));
					break;
				case GL_SAMPLER_2D:
					{
						xProgramTextureVariable* texture = (xProgramTextureVariable*)it->Variable;
						glActiveTexture(GL_TEXTURE0);
						if (texture->mTexture)				
							glBindTexture(GL_TEXTURE_2D, texture->mTexture->pImpl->mTexture);
						else
							glBindTexture(GL_TEXTURE_2D, 0);
					}
					break;
				}
			}

			for (GLuint i = 0; i < program_impl->mBuffers.Size(); i++)
			{
				xConstantBuffer* buffer = program_impl->mBuffers[i];
				buffer->Flush();
				glBindBuffer(GL_UNIFORM_BUFFER, buffer->pImpl->mUBO);
			}
		}
	}
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
	pImpl->mIndexBufferChanged = false;
	pImpl->mVertexBufferChanged = false;

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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
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
	glViewport(0, 0, 800, 600);
	glClearColor(color.R / 255.f, color.G / 255.f, color.B / 255.f, color.A / 255.f);
	glClearDepth(100.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void xRenderDevice::SetProgram(xProgram* program)
{
	pImpl->mProgram = program;
	if (pImpl->mProgram)
	{
		xProgram::Impl* program_impl = pImpl->mProgram->pImpl;
		glUseProgram(program_impl->mProgram);
	}
	else
		glUseProgram(0);
}

void xRenderDevice::SetIndexBuffer(xIndexBuffer* buffer)
{
	pImpl->mIndexBuffer = buffer;
	pImpl->mIndexBufferChanged = true;	
}

void xRenderDevice::SetVertexBuffer(xVertexBuffer* buffer)
{
	pImpl->mVertexBuffer = buffer;
	pImpl->mVertexBufferChanged = true;
}

xFORCE_INLINE
GLenum GetMode(xPrimitiveType::Enum primitive_type)
{
	switch (primitive_type)
	{
	case xPrimitiveType::PointList:
		return GL_POINTS;
	case xPrimitiveType::LineList:
		return GL_LINES;
	case xPrimitiveType::LineStrip:
		return GL_LINE_STRIP;					
	case xPrimitiveType::TriangleList:
		return GL_TRIANGLES;
	case xPrimitiveType::TriangleStrip:
		return GL_TRIANGLE_STRIP;
	default:
		return GL_POINTS;
	}
}

void xRenderDevice::DrawPrimitive(xPrimitiveType::Enum type, xUInt32 start_vertex, xUInt32 vertex_count)
{
	pImpl->BindNecessaryData();
	GLenum mode = GetMode(type);	
	glDrawArrays(mode, start_vertex, vertex_count);
}

void xRenderDevice::DrawIndexedPrimitive(xPrimitiveType::Enum type, xUInt32 base_vertex, xUInt32 start_index, xUInt32 index_count)
{
	pImpl->BindNecessaryData();
	xIndexBuffer* index_buffer = pImpl->mIndexBuffer;
	if (index_buffer)
	{
		GLenum mode = GetMode(type);	
		GLenum type = index_buffer->Format() == xIndexFormat::UInt16 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT;
		size_t sz = index_buffer->Format() == xIndexFormat::UInt16 ? sizeof(xUInt16) : sizeof(xUInt32);
		glDrawElementsBaseVertex(mode, index_count, type, BUFFER_OFFSET(start_index*sz), base_vertex);
	}
}

void xRenderDevice::Present()
{	
}