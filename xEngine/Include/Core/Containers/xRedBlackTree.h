#pragma once

template <typename TYPE>
class xRedBlackTree
{
	class Node;
public:
	class Iterator
	{
		friend class xRedBlackTree<TYPE>;
	public:
		Iterator();
		Iterator(const Iterator& other);

		const Iterator& operator = (const Iterator& other);
		bool operator != (const Iterator& other) const;
		bool operator == (const Iterator& other) const;
		const Iterator& operator ++ ();
		Iterator operator ++ (int);

		TYPE* operator -> () const;
		TYPE& operator * () const;
		operator bool () const;
	protected:
		Iterator(Node* node);
	private:
		Node* mNode;
	};

	xRedBlackTree();
	~xRedBlackTree();

	Iterator Insert(const TYPE& value);
	void Remove(const Iterator& iterator);

	size_t Size() const;
	bool IsEmpty() const;
	void Clear();
	Iterator Begin() const;
	Iterator End() const;
	Iterator Find(const TYPE& value) const;
protected:
	struct Node
	{	
		enum Color
		{
			Red = 0,
			Black
		};

		Node*	mParent;
		Node*	mLeft;
		Node*	mRight;
		Color	mColor;
		TYPE	mValue;

		Node(Color color);
		Node(const TYPE& value);

		Node* FindNext() const;
	};

	static Node	mSentinel;
	
	Node*   mRoot;
	size_t  mSize;

	void Rebalance(Node* node);
	void RebalanceAfterErase(Node* parent, Node* node);
	void RotateLeft(Node* node);
	void RotateRight(Node* node);
	void DeleteNode(Node* node, bool recursive);
};

#include "xRedBlackTree.inl"