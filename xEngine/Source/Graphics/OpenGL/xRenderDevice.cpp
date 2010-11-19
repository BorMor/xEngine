#include "xEngine.h"
#include "xPrerequisites.h"
#include "xMaterialImpl.h"
#include "xVertexBufferImpl.h"
#include "xRenderContext.h"


struct xRenderDevice::Impl
{
	xMaterial*		mMaterial;
	xRenderContext*	mContext;
};	

xRenderDevice::xRenderDevice(xRenderWindow* window)
{
	pImpl = new Impl();
	pImpl->mContext = new xRenderContext(window);

	xOpenGL::Init();
	
	pImpl->mMaterial = 0;	
}

xRenderDevice::~xRenderDevice()
{
	xOpenGL::Shutdown();

	xSAFE_DELETE(pImpl->mContext);
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
	pImpl->mContext->SwapBuffers();
}