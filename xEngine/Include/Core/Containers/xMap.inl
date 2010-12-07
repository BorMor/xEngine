template <typename KEYTYPE, typename VALUETYPE>
xMap<KEYTYPE, VALUETYPE>::xMap()
{
}

template <typename KEYTYPE, typename VALUETYPE>
xMap<KEYTYPE, VALUETYPE>::xMap(const xMap& other)
	: mTree(other.mTree)
{
}

template <typename KEYTYPE, typename VALUETYPE>
xMap<KEYTYPE, VALUETYPE>::~xMap()
{
}

template <typename KEYTYPE, typename VALUETYPE>
typename xMap<KEYTYPE, VALUETYPE>::Iterator xMap<KEYTYPE, VALUETYPE>::Insert(const KEYTYPE& key, const VALUETYPE& value)
{
	return mTree.Insert(xKeyValuePair<KEYTYPE, VALUETYPE>(key, value));
}

template <typename KEYTYPE, typename VALUETYPE>
void xMap<KEYTYPE, VALUETYPE>::Remove(const Iterator& iterator)
{
	mTree.Remove(iterator);
}

template <typename KEYTYPE, typename VALUETYPE>
void xMap<KEYTYPE, VALUETYPE>::Remove(const KEYTYPE& key)
{
	TreeType::Iterator it = mTree.Find(key);
	if (it != mTree.End())
		Remove(it);
}

template <typename KEYTYPE, typename VALUETYPE>
size_t xMap<KEYTYPE, VALUETYPE>::Size() const
{
	return mTree.Size();
}

template <typename KEYTYPE, typename VALUETYPE>
bool xMap<KEYTYPE, VALUETYPE>::IsEmpty() const
{
	return mTree.IsEmpty();
}

template <typename KEYTYPE, typename VALUETYPE>
void xMap<KEYTYPE, VALUETYPE>::Clear()
{
	mTree.Clear();
}

template <typename KEYTYPE, typename VALUETYPE>
typename xMap<KEYTYPE, VALUETYPE>::Iterator xMap<KEYTYPE, VALUETYPE>::Begin() const
{
	return mTree.Begin();
}

template <typename KEYTYPE, typename VALUETYPE>
typename xMap<KEYTYPE, VALUETYPE>::Iterator xMap<KEYTYPE, VALUETYPE>::End() const
{
	return mTree.End();
}

template <typename KEYTYPE, typename VALUETYPE>
typename xMap<KEYTYPE, VALUETYPE>::Iterator xMap<KEYTYPE, VALUETYPE>::Find(const KEYTYPE& key) const
{
	return mTree.Find(key);
}

template <typename KEYTYPE, typename VALUETYPE>
VALUETYPE& xMap<KEYTYPE, VALUETYPE>::operator[](const KEYTYPE& key) const
{
	static VALUETYPE dummy;

	TreeType::Iterator it = mTree.Find(key);
	if (it != mTree.End())
		return it->Value();
	else	
		return dummy;
}

template <typename KEYTYPE, typename VALUETYPE>
bool xMap<KEYTYPE, VALUETYPE>::Contains(const KEYTYPE& key) const
{
	return mTree.Find(key) != mTree.End();
}