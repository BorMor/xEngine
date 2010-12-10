#pragma once

namespace Internal
{
	template<typename KEYTYPE, typename VALUETYPE>
	struct xMapTraits
	{
		typedef KEYTYPE								KeyType;
		typedef xKeyValuePair<KEYTYPE, VALUETYPE>	ValueType;

		static const KeyType& Key(const ValueType& value)
		{
			return value.Key();
		}
	};
}

template <typename KEYTYPE, typename VALUETYPE>
class xMap
{
	typedef Internal::xRedBlackTreeBase<Internal::xMapTraits<KEYTYPE, VALUETYPE>> TreeType;
public:
	typedef typename TreeType::Iterator Iterator;

	xMap();
	~xMap();

	Iterator Insert(const KEYTYPE& key, const VALUETYPE& value);
	void Remove(const Iterator& iterator);
	void Remove(const KEYTYPE& key);

	size_t Size() const;
	bool IsEmpty() const;
	void Clear();

	Iterator Begin() const;
	Iterator End() const;
	Iterator Find(const KEYTYPE& key) const;

	VALUETYPE& operator[](const KEYTYPE& key) const;
	bool Contains(const KEYTYPE& key) const;	
protected:	
	TreeType	mTree;
private:
	xMap(const xMap& other);
};


#include "xMap.inl"
