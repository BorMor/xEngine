#pragma once

namespace Internal
{
	template <typename TYPE>
	struct xRedBlackTreeTraits
	{
		typedef TYPE KeyType;
		typedef TYPE ValueType;

		static const KeyType& Key(const ValueType& value)
		{
			return value;
		}
	};


	template <typename TRAITS>
	class xRedBlackTreeBase
	{
	protected:
		struct Node;
	public:
		typedef typename TRAITS::ValueType	TYPE;
		typedef typename TRAITS::KeyType	KEYTYPE;

		class Iterator
		{
			friend class xRedBlackTreeBase<TRAITS>;
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

		xRedBlackTreeBase();
		virtual ~xRedBlackTreeBase();

		Iterator Insert(const TYPE& value);
		void Remove(const Iterator& iterator);

		size_t Size() const;
		bool IsEmpty() const;
		void Clear();

		Iterator Begin() const;
		Iterator End() const;
		Iterator Find(const KEYTYPE& key) const;
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
			Node(const Node& other);

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
	private:
		xRedBlackTreeBase(const xRedBlackTreeBase& other);
	};
}

template <typename TYPE>
class xRedBlackTree : public Internal::xRedBlackTreeBase<Internal::xRedBlackTreeTraits<TYPE> >
{
};

#include "xRedBlackTree.inl"
