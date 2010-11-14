#include "xEngine.h"
#include "xMatchImpl.h"

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
	pImpl = new Impl;
}

xMatchCollection::xMatchCollection(xMatchCollection&& other)
{	
	pImpl = other.pImpl;
	other.pImpl = 0;
}

xMatchCollection::~xMatchCollection()
{
	if (pImpl)
	{
		for (auto it = pImpl->mMatches.begin(); it != pImpl->mMatches.end(); ++it)
			delete *it;
		xSAFE_DELETE(pImpl);
	}
}

const xMatch& xMatchCollection::operator[](int index) const
{
	return *(pImpl->mMatches[index]);
}

size_t xMatchCollection::Count() const
{
	return pImpl->mMatches.size();
}