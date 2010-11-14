template <typename TYPE>
xList<TYPE>::Iterator::Iterator()
	: mNode(NULL)
{
}

template <typename TYPE>
xList<TYPE>::Iterator::Iterator(const Iterator& other)
	: mNode(other.mNode)
{
}

template <typename TYPE>
xList<TYPE>::Iterator::Iterator(Node* node)
	: mNode(node)
{
}
template <typename TYPE>
const typename xList<TYPE>::Iterator& xList<TYPE>::Iterator::operator = (const Iterator& other)
{
	if (&other != this)
		this->mNode = other.mNode;
	return *this;
}

template <typename TYPE>
bool xList<TYPE>::Iterator::operator != (const Iterator& other) const
{
	return mNode != other.mNode;
}

template <typename TYPE>
bool xList<TYPE>::Iterator::operator == (const Iterator& other) const
{
	return mNode == other.mNode;
}

template <typename TYPE>
const typename xList<TYPE>::Iterator& xList<TYPE>::Iterator::operator ++ ()
{
	mNode = mNode->mNext;
	return *this;
}

template <typename TYPE>
typename xList<TYPE>::Iterator xList<TYPE>::Iterator::operator ++ (int)
{
	typename xList<TYPE>::Iterator it(mNode);
	mNode = mNode->mNext;
	return it;
}

template <typename TYPE>
const typename xList<TYPE>::Iterator& xList<TYPE>::Iterator::operator -- ()
{
	mNode = mNode->mPrev;
	return *this;
}

template <typename TYPE>
typename xList<TYPE>::Iterator xList<TYPE>::Iterator::operator -- (int)
{
	typename xList<TYPE>::Iterator it(mNode);
	mNode = mNode->mPrev;
	return it;
}

template <typename TYPE>
TYPE* xList<TYPE>::Iterator::operator -> () const
{
	return &(mNode->Value());
}

template <typename TYPE>
TYPE& xList<TYPE>::Iterator::operator * () const
{
	return mNode->Value();
}

template <typename TYPE>
xList<TYPE>::Iterator::operator bool () const
{
	return (mNode != NULL);
}

template <typename TYPE>
xList<TYPE>::xList()
	: mFront(NULL), mBack(NULL), mSize(0)
{
}

template <typename TYPE>
xList<TYPE>::~xList()
{
	Clear();
}

template <typename TYPE>
size_t xList<TYPE>::Size() const
{
	return mSize;
}

template <typename TYPE>
bool xList<TYPE>::IsEmpty() const
{
	return mSize == 0;
}

template <typename TYPE>
TYPE& xList<TYPE>::Front() const
{
	return mFront->Value();
}

template <typename TYPE>
TYPE& xList<TYPE>::Back() const
{
	return mBack->Value();
}

template <typename TYPE>
void xList<TYPE>::Clear()
{
	Node* node = NULL;
	while (node = mFront)
	{
		mFront = node->mNext;
		delete node;
	}
	mFront = NULL;
	mBack = NULL;
	mSize = 0;
}

template <typename TYPE>
void xList<TYPE>::AddFront(const TYPE& item)
{
	Node* node = new Node(item);
	if (mFront)
	{
		mFront->mPrev = node;
		node->mNext = mFront;
		mFront = node;
	}
	else
	{
		mFront = node;
		mBack = node;
	}
	++mSize;
}

template <typename TYPE>
void xList<TYPE>::AddBack(const TYPE& item)
{
	Node* node = new Node(item);
	if (mBack)
	{
		mBack->mNext = node;
		node->mPrev = mBack;
		mBack = node;
	}
	else
	{
		mFront = node;
		mBack = node;
	}
	++mSize;
}

template <typename TYPE>
void xList<TYPE>::InsertAfter(const Iterator& iterator, const TYPE& item)
{
	Node* node = new Node(item);
	Node* it_node = iterator.mNode;
	node->mPrev = it_node;
	node->mNext = it_node->mNext;
	if (node->mNext == NULL)
		mBack = node;
	else
		node->mNext->mPrev = node;
	it_node->mNext = node;
	++mSize;
}

template <typename TYPE>
void xList<TYPE>::InsertBefore(const Iterator& iterator, const TYPE& item)
{
	Node* node = new Node(item);
	Node* it_node = iterator.mNode;
	node->mNext = it_node;
	node->mPrev = it_node->mPrev;
	if (node->mPrev == NULL)
		mFront = node;
	else
		node->mPrev->mNext = node;
	it_node->mPrev = node;
	++mSize;
}

template <typename TYPE>
typename xList<TYPE>::Iterator xList<TYPE>::Begin() const
{
	if (mFront)
		return typename xList<TYPE>::Iterator(mFront);
	else
		return NULL;
}

template <typename TYPE>
typename xList<TYPE>::Iterator xList<TYPE>::End() const
{
	return NULL;
}

template <typename TYPE>
typename xList<TYPE>::Iterator xList<TYPE>::Find(const TYPE& value) const
{
	Node* node = mFront;
	while (node)
	{
		if (node->mValue == value)
			return Iterator(node);
		node = node->mNext;
	}
	return NULL;
}

template <typename TYPE>
void xList<TYPE>::Remove(const Iterator& iterator)
{
	Node* it_node = iterator.mNode;
	if (it_node->mPrev)
		it_node->mPrev->mNext = it_node->mNext;
	if (it_node->mNext)
		it_node->mNext->mPrev = it_node->mPrev;
	if (it_node == mBack)
		mBack = it_node->mPrev;
	if (it_node == mFront)
		mFront = it_node->mNext;
	delete it_node;
	--mSize;
}

template <typename TYPE>
xList<TYPE>::Node::Node(const TYPE& value)
	: mValue(value), mNext(NULL), mPrev(NULL)
{
}

template <typename TYPE>
xList<TYPE>::Node::~Node()
{
}

template <typename TYPE>
TYPE& xList<TYPE>::Node::Value()
{
	return mValue;
}
