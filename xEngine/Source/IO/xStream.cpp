#include "xEngine.h"

xStream::xStream(xAccessMode::Enum access_mode)
	: mAccessMode(access_mode)
{

}

xStream::~xStream()
{
	Close();
}

void xStream::Open()
{
	mIsOpen = true;
}

void xStream::Close()
{
	mIsOpen = false;
}

bool xStream::IsOpen() const
{
	return mIsOpen;
}