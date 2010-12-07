#include "Prerequisites.h"

xTEST(RedBlackTree)
{
	typedef xRedBlackTree<int> xIntRBTree;
	xIntRBTree tree;
	xCHECK(tree.Size() == 0)
	xCHECK(tree.IsEmpty())
	tree.Insert(4);
	tree.Insert(15);
	xCHECK(!tree.IsEmpty())
	xCHECK(tree.Size() == 2)
	xIntRBTree::Iterator it1 = tree.Insert(14);
	xCHECK(it1)
	tree.Insert(7);
	tree.Insert(9);
	xCHECK(tree.Size() == 5)
	tree.Insert(9);
	xCHECK(tree.Size() == 5)
	xCHECK(*tree.Begin() == 4)

	int sum = 0;
	for (xIntRBTree::Iterator it = tree.Begin(); it != tree.End(); ++it)
		sum += *it;
	xCHECK(sum == 49)
	xIntRBTree::Iterator it2 = tree.Find(14);
	xCHECK(it2 != tree.End())
	xCHECK(it1 == it2)
	tree.Remove(it1);
	xCHECK(tree.Size() == 4)
	sum = 0;
	for (xIntRBTree::Iterator it = tree.Begin(); it != tree.End(); ++it)
		sum += *it;
	xCHECK(35);
	tree.Clear();
	xCHECK(tree.IsEmpty());
}