#pragma once

struct xIndexBuffer::Impl
{
	ID3D10Buffer*	mBuffer;
	void*			mData;
};