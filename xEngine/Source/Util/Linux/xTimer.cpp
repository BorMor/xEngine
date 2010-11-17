#include "xEngine.h"

#include <sys/time.h>

struct xTimer::Impl
{
    timeval mTime;
};

xTimer::xTimer()
{
	pImpl = new Impl;
	Reset();
}

xTimer::~xTimer()
{
	xSAFE_DELETE(pImpl);
}

void xTimer::Reset()
{
    gettimeofday(&pImpl->mTime, 0);
}

float xTimer::ElapsedTime()
{
    timeval t;
	gettimeofday(&t, 0);

	return (float)(t.tv_sec - pImpl->mTime.tv_sec) + (float)(t.tv_usec - pImpl->mTime.tv_usec) / 1000000.f;
}
