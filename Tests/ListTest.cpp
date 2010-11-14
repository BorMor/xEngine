#include "Prerequisites.h"

xTEST(List)
{
	typedef xList<xString> xStringList;
	xStringList list;
	xCHECK(list.Size() == 0)
	list.AddBack("dog");
	xCHECK(list.Size() == 1)
	xCHECK(list.Front() == "dog")
	xCHECK(list.Back() == "dog")
	list.AddFront("cat");
	xCHECK(list.Size() == 2)
	xCHECK(list.Front() == "cat")
	xCHECK(list.Back() == "dog")
	list.AddBack("bird");
	xCHECK(list.Size() == 3)
	xCHECK(list.Front() == "cat")
	xCHECK(list.Back() == "bird")
	int n = 0;
	for (xStringList::Iterator it = list.Begin(); it != list.End(); ++it)
	{
		if (n == 0)
			xCHECK((*it) == "cat")
		else if (n == 1)
			xCHECK((*it) == "dog")
		else if (n == 2)
			xCHECK((*it) == "bird")
		n++;
	}
	xCHECK(n == 3);
	list.Remove(list.Begin());
	xCHECK(list.Size() == 2)
	xCHECK(list.Front() == "dog")
	xCHECK(list.Back() == "bird")
	list.Remove(list.Begin()++);
	xCHECK(list.Size() == 1);
	xCHECK(list.Front() == "bird")
	xCHECK(list.Back() == "bird")
	n = 0;
	for (xStringList::Iterator it = list.Begin(); it != list.End(); ++it)
		n++;
	xCHECK(n == 1)
	list.Remove(list.Begin()++);
	xCHECK(list.Size() == 0)
	n = 0;
	for (xStringList::Iterator it = list.Begin(); it != list.End(); ++it)
		n++;
	xCHECK(n == 0)
	list.AddBack("dog");
	list.AddBack("cat");
	list.AddBack("bird");
	xStringList::Iterator it = list.Begin();	
	xStringList::Iterator it1 = ++it;
	xCHECK((*it1) == "cat")
	xStringList::Iterator it2 = it++;
	xCHECK((*it2) == "cat")
	xCHECK((*it) == "bird")
	list.Clear();
	xCHECK(list.Size() == 0)
}