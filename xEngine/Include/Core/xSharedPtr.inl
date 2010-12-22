template <typename TYPE>
xSharedPtr<TYPE>::xSharedPtr()
{
	mObject = NULL;
	mReferenceCount = NULL;
}

template <typename TYPE>
xSharedPtr<TYPE>::xSharedPtr(const xSharedPtr<TYPE>& other)
{
	mObject = other.mObject;
	mReferenceCount = other.mReferenceCount;
	if (mReferenceCount)
		++*mReferenceCount;
}

template <typename TYPE>
xSharedPtr<TYPE>::xSharedPtr(TYPE* object)
{
	mObject = object;
	if (mObject)
	{
		mReferenceCount = new xUInt32(0);
		IncRef();
	}
}

template <typename TYPE>
xSharedPtr<TYPE>::~xSharedPtr()
{
	DecRef();
}

template <typename TYPE>
xSharedPtr<TYPE>& xSharedPtr<TYPE>::operator = (const xSharedPtr<TYPE>& other)
{
	if (mObject)
		DecRef();
	mObject = other.mObject;
	mReferenceCount = other.mReferenceCount;
	IncRef();
	return *this;
}

template <typename TYPE>
xSharedPtr<TYPE>::operator const bool () const
{
	return (mReferenceCount != NULL);
}

template <typename TYPE>
bool xSharedPtr<TYPE>::operator ! () const
{
	return (mReferenceCount == NULL);
}

template <typename TYPE>
TYPE* xSharedPtr<TYPE>::operator -> ()
{
	return mObject;
}

template <typename TYPE>
const TYPE* xSharedPtr<TYPE>::operator -> () const
{
	return mObject;
}

template <typename TYPE>
TYPE& xSharedPtr<TYPE>::operator * ()
{
	return *mObject;
}

template <typename TYPE>
const TYPE& xSharedPtr<TYPE>::operator * () const
{
	return *mObject;
}

template <typename TYPE>
xSharedPtr<TYPE>::operator TYPE*() const
{
	return mObject;
}

template <typename TYPE>
bool xSharedPtr<TYPE>::operator == (const xSharedPtr& other) const
{
	return mObject == other.mObject;
}

template <typename TYPE>
bool xSharedPtr<TYPE>::operator != (const xSharedPtr& other) const
{
	return mObject != other.mObject;
}

template <typename TYPE>
void xSharedPtr<TYPE>::Reset()
{
	DecRef();
}

template <typename TYPE>
xUInt32 xSharedPtr<TYPE>::UseCount() const
{
	if (mReferenceCount == NULL)
		return 0;
	else
		return *mReferenceCount;
}

template <typename TYPE>
void xSharedPtr<TYPE>::IncRef()
{
	if (mReferenceCount)
		++*mReferenceCount;
}

template <typename TYPE>
void xSharedPtr<TYPE>::DecRef()
{
	if (mReferenceCount)
	{
		if (--*mReferenceCount == 0)
		{
			xSAFE_DELETE(mObject);
			xSAFE_DELETE(mReferenceCount);
		}
	}
}
