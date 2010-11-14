template<typename KEYTYPE, typename VALUETYPE>
xKeyValuePair<KEYTYPE, VALUETYPE>::xKeyValuePair()
{
}

template<typename KEYTYPE, typename VALUETYPE>
xKeyValuePair<KEYTYPE, VALUETYPE>::xKeyValuePair(const KEYTYPE& k, const VALUETYPE& v)
	: mKey(k), mValue(v)
{
}

template<typename KEYTYPE, typename VALUETYPE>
VALUETYPE& xKeyValuePair<KEYTYPE, VALUETYPE>::Value()
{
	return mValue;
}

template<typename KEYTYPE, typename VALUETYPE>
const KEYTYPE& xKeyValuePair<KEYTYPE, VALUETYPE>::Key() const
{
	return mKey;
}

template<typename KEYTYPE, typename VALUETYPE>
const VALUETYPE& xKeyValuePair<KEYTYPE, VALUETYPE>::Value() const
{
	return mValue;
}
