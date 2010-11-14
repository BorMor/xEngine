#pragma once

template <typename TYPE>
class xSharedPtr
{
public:
	xSharedPtr();
	xSharedPtr(const xSharedPtr& other);
	xSharedPtr(TYPE* object);
	~xSharedPtr();

	xSharedPtr& operator = (const xSharedPtr& other);
	operator const bool () const;
	bool operator ! () const;
	TYPE* operator -> ();
	const TYPE* operator -> () const;
	TYPE& operator * ();
	const TYPE& operator * () const;
	operator TYPE*() const;
	bool operator == (const xSharedPtr& other) const;
	bool operator != (const xSharedPtr& other) const;

	void Reset();
	xUInt32 UseCount() const;
protected:
	TYPE* mObject;
	xUInt32* mReferenceCount;

	void IncRef();
	void DecRef();
};

#include "xSharedPtr.inl"
