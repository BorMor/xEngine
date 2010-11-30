#pragma once

struct xVertexBuffer::Impl
{
	ID3D10Buffer*	mBuffer;
	xSharedPtr<xVertexFormat>	mVertexFormat;
	void*			mData;
//	GLuint	mVBO;
//	GLuint	mVAO;
};