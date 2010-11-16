#include "xEngine.h"

xMatch::xMatch()
	: mSuccess(false)
{
}

xMatch::xMatch(xMatch&& other)
{
	mSuccess = other.mSuccess;
	mIndex = other.mIndex;
	mLength = other.mLength;
	mValue = other.mValue;
}

bool xMatch::Success() const
{
	return mSuccess;
}

xMatchCollection::xMatchCollection()
{
}

xMatchCollection::xMatchCollection(xMatchCollection&& other)
{	
	std::swap(mMatches, other.mMatches);
}

xMatchCollection::~xMatchCollection()
{
	for (auto it = mMatches.Begin(); it != mMatches.End(); ++it)
		delete *it;
}

const xMatch& xMatchCollection::operator[](int index) const
{
	return *mMatches[index];
}

size_t xMatchCollection::Count() const
{
	return mMatches.Size();
}