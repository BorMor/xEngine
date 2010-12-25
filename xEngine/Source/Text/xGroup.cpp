#include "xEngine.h"

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
}

xGroupCollection::~xGroupCollection()
{
	for (xArray<xGroup*>::Iterator it = mGroups.Begin(); it != mGroups.End(); ++it)
			delete *it;
}

xGroupCollection::Iterator xGroupCollection::Begin() const
{
	return mGroups.Begin();
}

xGroupCollection::Iterator xGroupCollection::End() const
{
	return mGroups.End();
}

const xGroup& xGroupCollection::operator[](int index) const
{
	return *mGroups[index];
}

size_t xGroupCollection::Count() const
{
	return mGroups.Size();
}
