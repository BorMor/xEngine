
template <typename TYPE>
xRedBlackTree<TYPE>::Iterator::Iterator()
	: mNode(NULL)
{
}

template <typename TYPE>
xRedBlackTree<TYPE>::Iterator::Iterator(const Iterator& other)
	: mNode(other.mNode)
{
}

template <typename TYPE>
xRedBlackTree<TYPE>::Iterator::Iterator(Node* node)
	: mNode(node)
{
}
template <typename TYPE>
const typename xRedBlackTree<TYPE>::Iterator& xRedBlackTree<TYPE>::Iterator::operator = (const Iterator& other)
{
	if (&other != this)
		this->mNode = other.mNode;
	return *this;
}

template <typename TYPE>
bool xRedBlackTree<TYPE>::Iterator::operator != (const Iterator& other) const
{
	return mNode != other.mNode;
}

template <typename TYPE>
bool xRedBlackTree<TYPE>::Iterator::operator == (const Iterator& other) const
{
	return mNode == other.mNode;
}

template <typename TYPE>
const typename xRedBlackTree<TYPE>::Iterator& xRedBlackTree<TYPE>::Iterator::operator ++ ()
{
	mNode = mNode->FindNext();
	return *this;
}

template <typename TYPE>
typename xRedBlackTree<TYPE>::Iterator xRedBlackTree<TYPE>::Iterator::operator ++ (int)
{
	typename xRedBlackTree<TYPE>::Iterator it(mNode);
	mNode = mNode->FindNext();
	return it;
}

template <typename TYPE>
TYPE* xRedBlackTree<TYPE>::Iterator::operator -> () const
{
	return &(mNode->mValue);
}

template <typename TYPE>
TYPE& xRedBlackTree<TYPE>::Iterator::operator * () const
{
	return mNode->mValue;
}

template <typename TYPE>
xRedBlackTree<TYPE>::Iterator::operator bool () const
{
	return (mNode != NULL);
}


template <typename TYPE>
typename xRedBlackTree<TYPE>::Node xRedBlackTree<TYPE>::mSentinel(xRedBlackTree<TYPE>::Node::Black);

template <typename TYPE>
xRedBlackTree<TYPE>::xRedBlackTree()
	: mRoot(&mSentinel), mSize(0)
{

}

template <typename TYPE>
xRedBlackTree<TYPE>::~xRedBlackTree()
{
}

template <typename TYPE>
typename xRedBlackTree<TYPE>::Iterator xRedBlackTree<TYPE>::Insert(const TYPE& value)
{
	Node* node = NULL;
	if (mRoot == &mSentinel)
	{
		mRoot = new Node(value);
		mRoot->mColor = Node::Black;
		node = mRoot;
	}
	else
	{
		Node* parent = mRoot;
		Node** link = 0;
		while (true)
		{
			if (parent->mValue == value)
				return parent;
			link = (parent->mValue > value) ? &parent->mLeft : &parent->mRight;		
			if (*link == &mSentinel)
				break;
			else
			parent = *link;
		};
	
		node = new Node(value);
		*link = node;
		node->mParent = parent;

		Rebalance(node);		
	}
	
	mSize++;
	return Iterator(node);
}

template <typename TYPE>
void xRedBlackTree<TYPE>::Remove(const Iterator& iterator)
{
	Node* node = iterator.mNode;
	Node* to_remove = 0;
	if (node->mLeft == &mSentinel || node->mRight == &mSentinel)
		to_remove = node;
	else
	{
		to_remove = node->mRight;
		while (to_remove->mLeft != &mSentinel)
			to_remove = to_remove->mLeft;
	}
	Node* child = (to_remove->mLeft != &mSentinel) ? to_remove->mLeft : to_remove->mRight;
	if (child != &mSentinel)
		child->mParent = to_remove->mParent;
	if (to_remove->mParent != &mSentinel)
	{
		if (to_remove == to_remove->mParent->mLeft)
			to_remove->mParent->mLeft = child;
		else
			to_remove->mParent->mRight = child;
	}	
	else
		mRoot = child;
	if (to_remove != node)
		node->mValue = to_remove->mValue;
	if (to_remove->mColor == Node::Black)
		RebalanceAfterErase(to_remove->mParent, child);

	DeleteNode(to_remove, false);
	mSize--;
}

template <typename TYPE>
size_t xRedBlackTree<TYPE>::Size() const
{
	return mSize;
}

template <typename TYPE>
bool xRedBlackTree<TYPE>::IsEmpty() const
{
	return mSize == 0;
}

template <typename TYPE>
void xRedBlackTree<TYPE>::Clear()
{
	if (mRoot != &mSentinel)
	{
		DeleteNode(mRoot, true);
		mSize = 0;
	}
}

template <typename TYPE>
typename xRedBlackTree<TYPE>::Iterator xRedBlackTree<TYPE>::Begin() const
{
	Node* node = NULL;
	if (mRoot != &mSentinel)
	{
		node = mRoot;
		while (node->mLeft != &mSentinel)
			node = node->mLeft;
	}
	return xRedBlackTree<TYPE>::Iterator(node);
}

template <typename TYPE>
typename xRedBlackTree<TYPE>::Iterator xRedBlackTree<TYPE>::End() const
{
	return NULL;
}

template <typename TYPE>
typename xRedBlackTree<TYPE>::Iterator xRedBlackTree<TYPE>::Find(const TYPE& value) const
{
	Node* node = mRoot;
	while (node != &mSentinel)
	{
		if (node->mValue == value)
			return Iterator(node);
		else
			node = (value < node->mValue) ? node->mLeft : node->mRight;
	}
	return End();
}

template <typename TYPE>
void xRedBlackTree<TYPE>::Rebalance(Node* node)
{
	while (node != mRoot && node->mParent->mColor == Node::Red)
	{
		Node* parent = node->mParent;
		if (parent == parent->mParent->mRight)
		{
			Node* uncle = parent->mParent->mLeft;
			if (uncle->mColor == Node::Red)
			{
				node->mParent->mColor = Node::Black;
				uncle->mColor = Node::Black;
				uncle->mParent->mColor = Node::Red;
				node = uncle->mParent;
			}
			else
			{
				if (node == node->mParent->mLeft)
				{
					node = node->mParent;
					RotateRight(node);
				}
				node->mParent->mColor = Node::Black;
				node->mParent->mParent->mColor = Node::Red;
				RotateLeft(node->mParent->mParent);
			}
		}
		else
		{
			Node* uncle = parent->mParent->mRight;
			if (uncle->mColor == Node::Red)
			{
				node->mParent->mColor = Node::Black;
				uncle->mColor = Node::Black;
				uncle->mParent->mColor = Node::Red;
				node = uncle->mParent;
			}
			else
			{
				if (node == node->mParent->mRight)
				{
					node = node->mParent;
					RotateLeft(node);
				}
				node->mParent->mColor = Node::Black;
				node->mParent->mParent->mColor = Node::Red;
				RotateRight(node->mParent->mParent);
			}
		}
	}	
	mRoot->mColor = Node::Black;
}

template <typename TYPE>
void xRedBlackTree<TYPE>::RebalanceAfterErase(Node* parent, Node* node)
{
	while (node != mRoot && node->mColor == Node::Black)
	{
		if (node == parent->mLeft)
		{
			Node* sibling = parent->mRight;
			if (sibling->mColor == Node::Red)
			{
				sibling->mColor = Node::Black;
				parent->mColor = Node::Red;
				RotateLeft(parent);
				sibling = parent->mRight;
			}	
			if (sibling->mLeft->mColor == Node::Black && sibling->mRight->mColor == Node::Black)
			{
				sibling->mColor = Node::Red;
				node = parent;
			}
			else
			{
				if (sibling->mRight->mColor == Node::Black)
				{
					sibling->mLeft->mColor = Node::Black;
					sibling->mColor = Node::Red;
					RotateRight(sibling);
					sibling = parent->mRight;
				}
				sibling->mColor = parent->mColor;
				parent->mColor = Node::Black;
				sibling->mRight->mColor = Node::Black;
				RotateLeft(parent);
				node = mRoot;
			}
		}
		else
		{
			Node* sibling = parent->mLeft;
			if (sibling->mColor == Node::Red)
			{
				sibling->mColor = Node::Black;
				parent->mColor = Node::Red;
				RotateRight(parent);
				sibling = parent->mLeft;
			}	
			if (sibling->mRight->mColor == Node::Black && sibling->mLeft->mColor == Node::Black)
			{
				sibling->mColor = Node::Red;
				node = parent;
			}
			else
			{
				if (sibling->mLeft->mColor == Node::Black)
				{
					sibling->mRight->mColor = Node::Black;
					sibling->mColor = Node::Red;
					RotateLeft(sibling);
					sibling = parent->mLeft;
				}
				sibling->mColor = parent->mColor;
				parent->mColor = Node::Black;
				sibling->mLeft->mColor = Node::Black;
				RotateRight(parent);
				node = mRoot;
			}
		}
		parent = node->mParent;
	}
	node->mColor = Node::Black;
}

template <typename TYPE>
void xRedBlackTree<TYPE>::RotateLeft(Node* node)
{
	Node* right = node->mRight;
	
	node->mRight = right->mLeft;	
	if (right->mLeft != &mSentinel)
		right->mLeft->mParent = node;
	right->mLeft = node;

	right->mParent = node->mParent;		
	
	if (node == node->mParent->mLeft)
		node->mParent->mLeft = right;
	else
		node->mParent->mRight = right;

	node->mParent = right;
	
	if (mRoot == node)
		mRoot = right;
}

template <typename TYPE>
void xRedBlackTree<TYPE>::RotateRight(Node* node)
{
	Node* left = node->mLeft;
	
	node->mLeft = left->mRight;	
	if (left->mRight != &mSentinel)
		left->mRight->mParent = node;
	left->mRight = node;

	left->mParent = node->mParent;	
	
	if (node == node->mParent->mLeft)
		node->mParent->mLeft = left;
	else
		node->mParent->mRight = left;

	node->mParent = left;	
	
	if (mRoot == node)
		mRoot = left;
}

template <typename TYPE>
void xRedBlackTree<TYPE>::DeleteNode(Node* node, bool recursive)
{
	if (recursive)
	{
		if (node->mLeft != &mSentinel)
			DeleteNode(node->mLeft, true);
		if (node->mRight != &mSentinel)
			DeleteNode(node->mRight, true);
	}
	if (node == mRoot)
		mRoot = &mSentinel;
	delete node;
}

template <typename TYPE>
xRedBlackTree<TYPE>::Node::Node(Color color)
{
	mColor = color;
	mParent = &mSentinel;
	mLeft = &mSentinel;
	mRight = &mSentinel;			
}

template <typename TYPE>
xRedBlackTree<TYPE>::Node::Node(const TYPE& value)
{
	mColor = Node::Red;
	mParent = &mSentinel;
	mLeft = &mSentinel;
	mRight = &mSentinel;
	mValue = value;
}
template <typename TYPE>
typename xRedBlackTree<TYPE>::Node* xRedBlackTree<TYPE>::Node::FindNext() const
{
	Node* next = NULL;
	if (mRight != &mSentinel)
	{
		next = mRight;
		while (next->mLeft != &mSentinel)
			next = next->mLeft;
	}
	else if (mParent != &mSentinel)
	{
		if (this == mParent->mLeft)
			return mParent;
		else
		{
			next = (Node*)this;
			while (next->mParent != &mSentinel)
			{
				if (next == next->mParent->mRight)
					next = next->mParent;
				else
					return next->mParent;
			}
			next = 0;
		}
	}
	return next;
}
