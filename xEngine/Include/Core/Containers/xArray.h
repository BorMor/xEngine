#pragma once

template <typename TYPE>
class xArray
{
public:
	typedef TYPE* Iterator;

	xArray();
	explicit xArray(size_t size);	
	xArray(const xArray& other);
	xArray(xArray&& other);
	~xArray();

	TYPE& operator[] (size_t i);
	const TYPE& operator[] (size_t i) const;

	size_t Size() const;
	size_t Capacity() const;
	bool IsEmpty() const;
	void Clear();
	void AddFront(const TYPE& item);
	void AddBack(const TYPE& item);
	void InsertAfter(size_t index, const TYPE& item);
	void InsertAfter(const Iterator& iterator, const TYPE& item);
	void InsertBefore(size_t index, const TYPE& item);
	void InsertBefore(const Iterator& iterator, const TYPE& item);
	Iterator Begin() const;
	Iterator End() const;
	Iterator Find(const TYPE& value) const;
	void Remove(const Iterator& iterator);
	void Resize(size_t n);
protected:
	TYPE*	mBegin;
	TYPE*	mEnd;
	TYPE*	mAllocationEnd;

	void Grow();
	void Shrink(size_t new_size);
	void ReAlloc(size_t capacity, bool discard_old = false);		
};

#include "xArray.inl"
