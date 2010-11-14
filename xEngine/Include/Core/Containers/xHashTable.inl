template <typename KEYTYPE, typename VALUETYPE>
xHashTable<KEYTYPE, VALUETYPE>::xHashTable(int table_size)
	: mTable(NULL), mTableSize(table_size), mSize(0)
{
	mTable = new Node* [mTableSize];
	ZeroMemory(mTable, mTableSize*sizeof(Node*));
}

template <typename KEYTYPE, typename VALUETYPE>
xHashTable<KEYTYPE, VALUETYPE>::~xHashTable()
{
	Clear();
	xSAFE_ARRAY_DELETE(mTable);
}

template <typename KEYTYPE, typename VALUETYPE>
void xHashTable<KEYTYPE, VALUETYPE>::Add(const KEYTYPE& key, const VALUETYPE& value)
{
	xASSERT(Contains(key) == false);
	xUInt32 hash = GetHash(key);
	Node* node = new Node(key, value);
	node->mNext = mTable[hash];
	mTable[hash] = node;
	mSize++;
}

template <typename KEYTYPE, typename VALUETYPE>
VALUETYPE& xHashTable<KEYTYPE, VALUETYPE>::operator[](const KEYTYPE& key) const
{
	xUInt32 hash = GetHash(key);
	Node* node = mTable[hash];
	while (node && node->Key() != key)
		node = node->mNext;
	return node->Value();
}

template <typename KEYTYPE, typename VALUETYPE>
bool xHashTable<KEYTYPE, VALUETYPE>::Contains(const KEYTYPE& key) const
{
	xUInt32 hash = GetHash(key);
	Node* node = mTable[hash];
	while (node && node->Key() != key)
		node = node->mNext;
	return (node != NULL);
}

template <typename KEYTYPE, typename VALUETYPE>
void xHashTable<KEYTYPE, VALUETYPE>::Clear()
{
	for (size_t i = 0; i < mTableSize; i++)
		if (mTable[i] != NULL)
		{
			Node* prev_node = NULL;
			Node* node = mTable[i];
			while (node)
			{
				prev_node = node;
				node = node->mNext;
				delete prev_node;
			}
			mTable[i] = NULL;
		}
	mSize = 0;
}

template <typename KEYTYPE, typename VALUETYPE>
void xHashTable<KEYTYPE, VALUETYPE>::Remove(const KEYTYPE& key)
{
	xUInt32 hash = GetHash(key);
	Node* prev_node = NULL;
	Node* node = mTable[hash];
	while (node && node->Key() != key)
	{
		prev_node = node;
		node = node->mNext;
	}
	if (node != NULL)
	{
		if (prev_node != NULL)
			prev_node->mNext = node->mNext;
		else
			mTable[hash] = node->mNext;
		delete node;
		mSize--;
	}
}

template <typename KEYTYPE, typename VALUETYPE>
size_t xHashTable<KEYTYPE, VALUETYPE>::Size() const
{
	return mSize;
}

template <typename KEYTYPE, typename VALUETYPE>
xHashTable<KEYTYPE, VALUETYPE>::Node::Node(const KEYTYPE& key, const VALUETYPE& value)
	: xKeyValuePair<KEYTYPE, VALUETYPE>(key, value), mNext(NULL)
{
}

template <typename KEYTYPE, typename VALUETYPE>
xHashTable<KEYTYPE, VALUETYPE>::Node::~Node()
{
}

template <typename KEYTYPE, typename VALUETYPE>
xUInt32 xHashTable<KEYTYPE, VALUETYPE>::GetHash(KEYTYPE key) const
{
	return xHash(key) % mTableSize;
}
