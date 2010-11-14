#pragma once

const size_t xSTRING_ALLOC_BASE = 20;
const size_t xSTRING_ALLOC_GRAN = 32;

class xEXPORT xString
{
public:
	xString();
	xString(const xString& other);
	xString(xString&& other);
	xString(const xChar* text);
	xString(const xChar* text, size_t length);
	~xString();

	void Set(const xString& str);
	void Set(const xChar* text);
	void Set(const xChar* text, size_t length);

	void Append(const xString& str);
	void Append(const xChar* text, size_t length);
	void Append(const xChar c);

	void Reserve(size_t nbytes);

	xString& operator =(const xString& text);
	xString& operator +=(const xString& text);
	xString& operator +=(const char* text);
	xString& operator +=(const char c);

	const xChar* c_str() const;
	xChar& operator[](int index);
	const xChar& operator[](int index) const;


	friend xString operator +(const xString& a, const xString& b);
	friend bool operator ==(const xString& a, const xString& b);
	friend bool operator !=(const xString& a, const xString& b);

	size_t Length() const;

	static xString Format(const xChar* format, ...);
protected:
	xChar*  mData;
	size_t  mLength;
	size_t  mAllocated;
	xChar   mBaseBuffer[xSTRING_ALLOC_BASE];

	void Init();
	void FreeData();
	void ReAlloc(size_t nbytes, bool keep_old);
	void EnsureAllocated(size_t nbytes, bool keep_old);
};

xUInt32 xHash(const xString& str);

#include "xString.inl"
