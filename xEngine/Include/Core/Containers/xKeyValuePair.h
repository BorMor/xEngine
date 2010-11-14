#pragma once

template <typename KEYTYPE, typename VALUETYPE>
class xKeyValuePair
{
public:
	xKeyValuePair();
	xKeyValuePair(const KEYTYPE& k, const VALUETYPE& v);

	VALUETYPE& Value();
	const KEYTYPE& Key() const;
	const VALUETYPE& Value() const;
protected:
	KEYTYPE		mKey;
	VALUETYPE	mValue;
};

#include "xKeyValuePair.inl"
