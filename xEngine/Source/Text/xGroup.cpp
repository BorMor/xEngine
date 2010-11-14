#include "xEngine.h"
#include "xGroupImpl.h"

xGroup::xGroup()
	: mIndex(0), mLength(0)
{
}

xGroup::~xGroup()
{
}

size_t xGroup::Index() const
{
	return mIndex;
}

size_t xGroup::Length() const
{
	return mLength;
}

xString xGroup::Value() const
{
	return mValue;
}


xGroupCollection::xGroupCollection()
{
	pImpl = new Impl;
}

xGroupCollection::~xGroupCollection()
{
	for (auto it = pImpl->mGroups.begin(); it != pImpl->mGroups.end(); ++it)
			delete *it;
	xSAFE_DELETE(pImpl);
}

const xGroup& xGroupCollection::operator[](int index) const
{
	return *pImpl->mGroups[index];
}

size_t xGroupCollection::Count() const
{
	return pImpl->mGroups.size();
}