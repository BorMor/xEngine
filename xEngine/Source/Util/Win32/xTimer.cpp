#include "xEngine.h"

struct xTimer::Impl
{
	LARGE_INTEGER	mFrequency;
	LARGE_INTEGER	mTime;
};

xTimer::xTimer()
{
	pImpl = new Impl;
	QueryPerformanceFrequency(&pImpl->mFrequency);
	Reset();
}

xTimer::~xTimer()
{
	xSAFE_DELETE(pImpl);
}

void xTimer::Reset()
{
	QueryPerformanceCounter(&pImpl->mTime);
}

float xTimer::ElapsedTime()
{
	LARGE_INTEGER t;
	QueryPerformanceCounter(&t);
	return (float)(t.QuadPart - pImpl->mTime.QuadPart) / (float)(pImpl->mFrequency.QuadPart);
}