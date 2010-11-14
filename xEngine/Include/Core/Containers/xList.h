#pragma once

template <typename TYPE>
class xList
{
protected:
	class Node;
public:
	class Iterator
	{
		friend class xList<TYPE>;
	public:
		Iterator();
		Iterator(const Iterator& other);

		const Iterator& operator = (const Iterator& other);
		bool operator != (const Iterator& other) const;
		bool operator == (const Iterator& other) const;
		const Iterator& operator ++ ();
		Iterator operator ++ (int);
		const Iterator& operator -- ();
		Iterator operator -- (int);
		TYPE* operator -> () const;
		TYPE& operator * () const;
		operator bool () const;
	protected:
		Iterator(Node* node);
	private:
		Node* mNode;
	};

	xList();
	~xList();

	size_t Size() const;
	bool IsEmpty() const;
	TYPE& Front() const;
	TYPE& Back() const;
	void Clear();
	void AddFront(const TYPE& item);
	void AddBack(const TYPE& item);
	void InsertAfter(const Iterator& iterator, const TYPE& item);
	void InsertBefore(const Iterator& iterator, const TYPE& item);
	Iterator Begin() const;
	Iterator End() const;
	Iterator Find(const TYPE& value) const;
	void Remove(const Iterator& iterator);
protected:
	class Node
	{
		friend class xList<TYPE>;
		friend class xList<TYPE>::Iterator;
	public:
		Node(const TYPE& value);
		~Node();

		TYPE& Value();
	protected:
		TYPE mValue;
		Node* mNext;
		Node* mPrev;
	};

	Node*   mFront;
	Node*   mBack;
	size_t  mSize;
};

#include "xList.inl"
