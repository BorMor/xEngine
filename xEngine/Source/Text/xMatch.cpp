#include "xEngine.h"

xMatch::xMatch()
	: mSuccess(false)
{
}

bool xMatch::Success() const
{
	return mSuccess;
}

xMatchCollection::xMatchCollection()
{
}

xMatchCollection::~xMatchCollection()
{
	for (auto it = mMatches.Begin(); it != mMatches.End(); ++it)
		delete *it;
}

xMatchCollection::Iterator xMatchCollection::Begin() const
{
	return mMatches.Begin();
}

xMatchCollection::Iterator xMatchCollection::End() const
{
	return mMatches.End();
}

const xMatch& xMatchCollection::operator[](int index) const
{
	return *mMatches[index];
}

size_t xMatchCollection::Count() const
{
	return mMatches.Size();
}