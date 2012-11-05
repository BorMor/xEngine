#pragma once

struct xVertexBuffer::Impl
{
	ID3D11Buffer*	mBuffer;
	xSharedPtr<xVertexFormat>	mVertexFormat;
	void*			mData;
};