#include "xEngine.h"
#include "xPrerequisites.h"
#include "xVertexBufferImpl.h"
#include "xVertexFormatImpl.h"

xVertexBuffer::xVertexBuffer(xVertexFormat* vertex_format, size_t vertex_count, size_t stride)
	: mStride(stride), mVertexCount(vertex_count)
{
	pImpl = new Impl;
	glGenBuffers(1, &pImpl->mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pImpl->mVBO);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * stride, NULL, GL_STATIC_DRAW);

	glGenVertexArrays(1, &pImpl->mVAO);
	
	glBindVertexArray(pImpl->mVAO);

	if (stride == 0)
		stride = vertex_format->VertexSize();
	
	const xVertexFormat::Impl::ElementList& elements = vertex_format->pImpl->mElements;

	for (xVertexFormat::Impl::ElementList::Iterator it = elements.Begin(); it != elements.End(); ++it)
	{					
		GLint size;
		GLenum type;
		GLboolean normalized;			

		switch (it->Type)
		{
		case xVertexElementType::Float:
			size = 1;
			type = GL_FLOAT;
			normalized = GL_FALSE;
			break;
		case xVertexElementType::Vector2:
			size = 2;
			type = GL_FLOAT;
			normalized = GL_FALSE;
			break;
		case xVertexElementType::Vector3:
			size = 3;
			type = GL_FLOAT;
			normalized = GL_FALSE;
			break;
		case xVertexElementType::Vector4:
			size = 4;
			type = GL_FLOAT;
			normalized = GL_FALSE;
			break;
		case xVertexElementType::Color:
			size = 4;
			type = GL_UNSIGNED_BYTE;
			normalized = GL_TRUE;
			break;
					
		};
		glVertexAttribPointer((int)it->Usage, size, type, normalized, stride, BUFFER_OFFSET(it->Offset));
		glEnableVertexAttribArray((int)it->Usage);
	}

	glBindVertexArray(0);
}


xVertexBuffer::~xVertexBuffer()
{
	glDeleteBuffers(1, &pImpl->mVAO);
	glDeleteBuffers(1, &pImpl->mVBO);
	xSAFE_DELETE(pImpl);
}

size_t xVertexBuffer::Stride() const
{
	return mStride;
}

size_t xVertexBuffer::VertexCount() const
{
	return mVertexCount;
}

size_t xVertexBuffer::SizeInBytes() const
{
    return mStride * mVertexCount;
}

void* xVertexBuffer::Lock()
{
	glBindBuffer(GL_ARRAY_BUFFER, pImpl->mVBO);
	return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void xVertexBuffer::Unlock()
{
	glBindBuffer(GL_ARRAY_BUFFER, pImpl->mVBO);
	glUnmapBuffer(GL_ARRAY_BUFFER);
}
