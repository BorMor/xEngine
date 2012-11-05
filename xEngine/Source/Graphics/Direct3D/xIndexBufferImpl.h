#pragma once

struct xIndexBuffer::Impl
{
	ID3D11Buffer*	mBuffer;
	void*			mData;
};