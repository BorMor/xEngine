const size_t xARRAY_INITIAL_SIZE = 16;

template<typename TYPE>
xArray<TYPE>::xArray()
	: mBegin(0), mEnd(0), mAllocationEnd(0)
{
}

template<typename TYPE>
xArray<TYPE>::xArray(size_t size)
	: mBegin(0), mEnd(0), mAllocationEnd(0)
{
	Resize(size);
}

template<typename TYPE>
xArray<TYPE>::xArray(const xArray& other)
	: mBegin(0), mEnd(0), mAllocationEnd(0)
{
	if (other.Size() == 0)
		return;
	ReAlloc(other.Capacity(), true);
	xCopyConstructN(mBegin, other.mBegin, other.Size());
	mEnd = mBegin + other.Size();
}

template<typename TYPE>
xArray<TYPE>::xArray(xArray&& other)
	: mBegin(0), mEnd(0), mAllocationEnd(0)
{
	std::swap(mBegin, other.mBegin);
	std::swap(mEnd, other.mEnd);
	std::swap(mAllocationEnd, other.mAllocationEnd);
}

template<typename TYPE>
xArray<TYPE>::~xArray()
{
	if (mBegin)
	{
		xDestructN(mBegin, mEnd-mBegin);	
		delete [] mBegin;
	}
}

template<typename TYPE>
TYPE& xArray<TYPE>::operator[] (size_t i)
{
	xASSERT(i < Size());
	return mBegin[i];
}

template<typename TYPE>
const TYPE& xArray<TYPE>::operator[] (size_t i) const
{
	xASSERT(i < Size());
	return mBegin[i];
}

template<typename TYPE>
size_t xArray<TYPE>::Size() const
{
	return mEnd - mBegin;
}

template<typename TYPE>
size_t xArray<TYPE>::Capacity() const
{
	return mAllocationEnd - mBegin;
}

template<typename TYPE>
bool xArray<TYPE>::IsEmpty() const
{
	return mSize == 0;
}

template<typename TYPE>
void xArray<TYPE>::Clear()
{
	if (mBegin)
	{
		xDestructN(mBegin, mEnd-mBegin);
		mEnd = mBegin;
	}
}

template<typename TYPE>
void xArray<TYPE>::AddFront(const TYPE& item)
{
	if (mBegin)
		InsertBefore(mBegin, item);
	else
		AddBack(item);
}

template<typename TYPE>
void xArray<TYPE>::AddBack(const TYPE& item)
{
	if (mEnd == mAllocationEnd)
		Grow();		
	*mEnd++ = item;
}

template<typename TYPE>
void xArray<TYPE>::InsertAfter(size_t index, const TYPE& item)
{
	if (mEnd == mAllocationEnd)
		Grow();

	Iterator it = mBegin + index +1;
	xMoveN(it + 1, it, Size() - index - 1);
	*it = item;

	++mEnd;
}

template<typename TYPE>
void xArray<TYPE>::InsertAfter(const Iterator& iterator, const TYPE& item)
{
	InsertAfter(iterator - mBegin, item);
}

template<typename TYPE>
void xArray<TYPE>::InsertBefore(size_t index, const TYPE& item)
{
	if (mEnd == mAllocationEnd)
		Grow();

	Iterator it = mBegin + index;
	xMoveN(it + 1, it, Size() - index);
	*it = item;

	++mEnd;
}

template<typename TYPE>
void xArray<TYPE>::InsertBefore(const Iterator& iterator, const TYPE& item)
{
	InsertBefore(iterator - mBegin, item);
}

template<typename TYPE>
typename xArray<TYPE>::Iterator xArray<TYPE>::Begin() const
{
	return mBegin;
}

template<typename TYPE>
typename xArray<TYPE>::Iterator xArray<TYPE>::End() const
{
	return mEnd;
}

template<typename TYPE>
typename xArray<TYPE>::Iterator xArray<TYPE>::Find(const TYPE& value) const
{
	for (auto it = mBegin; it != mEnd; ++it)
		if (*it == value)
			return it;
	return mEnd;
}

template<typename TYPE>
void xArray<TYPE>::Remove(const Iterator& iterator)
{
	xCopyN(iterator, iterator + 1, mEnd - iterator);
	--mEnd;
	xDestruct(mEnd);
}

template<typename TYPE>
void xArray<TYPE>::Resize(size_t n)
{
	if (n > Size())
	{
		const size_t capacity = Capacity();
		ReAlloc(capacity == 0 ? xARRAY_INITIAL_SIZE : (n > capacity * 2 ? n : capacity * 2));
		xConstructN(mBegin + capacity, Capacity() - capacity);
		mEnd = mBegin + n;
	}
	else
		Shrink(n);
}

template<typename TYPE>
void xArray<TYPE>::Grow()
{
	ReAlloc(mAllocationEnd == 0 ? xARRAY_INITIAL_SIZE : Capacity() * 2);
}

template<typename TYPE>
void xArray<TYPE>::Shrink(size_t new_size)
{
	const size_t to_shrink = Size() - new_size;
	xDestructN(mBegin + new_size, to_shrink);
	mEnd = mBegin + new_size;
}

template<typename TYPE>
void xArray<TYPE>::ReAlloc(size_t capacity, bool discard_old)
{
	const size_t old_size = Size();
	TYPE* new_data = new TYPE[capacity];
	if (mBegin)
	{
		if (discard_old)
			xDestructN(mBegin, old_size);
		else
			xCopyN(new_data, mBegin, old_size);
		delete [] mBegin;
	}
	mBegin = new_data;
	mEnd = mBegin + old_size;
	mAllocationEnd = mBegin + capacity;
}
