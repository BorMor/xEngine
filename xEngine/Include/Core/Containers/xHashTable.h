#pragma once

template <typename KEYTYPE, typename VALUETYPE>
class xHashTable
{
public:
	xHashTable(int table_size = 256);
	~xHashTable();

	void Add(const KEYTYPE& key, const VALUETYPE& value);
	VALUETYPE& operator[](const KEYTYPE& key) const;
	bool Contains(const KEYTYPE& key) const;
	void Clear();
	void Remove(const KEYTYPE& key);

	size_t Size() const;
protected:
	class Node : public xKeyValuePair<KEYTYPE, VALUETYPE>
	{
		friend class xHashTable<KEYTYPE, VALUETYPE>;
	public:
		Node(const KEYTYPE& key, const VALUETYPE& value);
		~Node();
	protected:
		Node* mNext;
	};

	Node**	mTable;
	xUInt32	mTableSize;
	size_t  mSize;

	xUInt32 GetHash(KEYTYPE key) const;
};

#include "xHashTable.inl"
