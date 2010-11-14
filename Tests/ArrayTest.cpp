#include "Prerequisites.h"



/*template<typename T>
void copy_n(const T* first, size_t n, T* result, int_to_type<false>)
{
	OutputDebugString("int_to_type<false>\n");
}

template<typename T>
void copy_n(const T* first, size_t n, T* result, int_to_type<true>)
{
	OutputDebugString("int_to_type<true>\n");
}
*/
//
//xTEST(Array)
//{
//	{
//		int n = 300000000;
//		copy_n(&n, 1, &result);
//
//		xList<int> l;
//		copy_n(&l, 1, &l);
//		/*int* arr = new int[n];
//		for (int i = 0; i < n; i++)
//			arr[i] = i;
//		int* first = arr;
//		int* last = arr + n;
//
//		int result;
//		
//		//	*result++ = *first++;
//		LARGE_INTEGER t1, t2, t3, t4;
//		QueryPerformanceCounter(&t1);
//		switch (n & 0x3)
//		{
//		case 0:
//			while (first != last)
//			{
//				result = *first++;
//		case 3:	result = *first++;
//		case 2: result = *first++;
//		case 1: result = *first++;
//			}
//		}
//		QueryPerformanceCounter(&t2);
//
//		first = arr;
//		QueryPerformanceCounter(&t3);
//		while (first != last)
//			result = *first++;
//		QueryPerformanceCounter(&t4);
//
//		MessageBox(0, xString::Format("dt1=%d dt2=%d result=%d", t2.LowPart - t1.LowPart, t4.LowPart - t3.LowPart, result).c_str(), "", MB_OK);
//
//		delete [] arr;*/
//	}
//	{
//		xArray<int> arr;
//		arr.AddFront(1);
//		xCHECK(arr.Size() == 1);
//		arr.AddFront(2);
//		xCHECK(arr.Size() == 2);
//		xCHECK(arr[0] == 2);
//		xCHECK(arr[1] == 1);		
//		//arr.Remove(arr.Begin());
//		xCHECK(arr[0] == 1);
//		xCHECK(arr.Size() == 1);		
//		arr.AddBack(3);
//		arr.AddBack(5);
//		arr.AddBack(7);
//		//auto it = arr.Find(5);
//		//xCHECK(it != arr.End());
//		//arr.Remove(it);
//		xCHECK(arr[2] == 7);
//	}
//	/*typedef xList<xString> xStringList;
//	xStringList list;
//	xCHECK(list.Size() == 0)
//	list.AddBack("dog");
//	xCHECK(list.Size() == 1)
//	xCHECK(list.Front() == "dog")
//	xCHECK(list.Back() == "dog")
//	list.AddFront("cat");
//	xCHECK(list.Size() == 2)
//	xCHECK(list.Front() == "cat")
//	xCHECK(list.Back() == "dog")
//	list.AddBack("bird");
//	xCHECK(list.Size() == 3)
//	xCHECK(list.Front() == "cat")
//	xCHECK(list.Back() == "bird")
//	int n = 0;
//	for (xStringList::Iterator it = list.Begin(); it != list.End(); ++it)
//	{
//		if (n == 0)
//			xCHECK((*it) == "cat")
//		else if (n == 1)
//			xCHECK((*it) == "dog")
//		else if (n == 2)
//			xCHECK((*it) == "bird")
//		n++;
//	}
//	xCHECK(n == 3);
//	list.Remove(list.Begin());
//	xCHECK(list.Size() == 2)
//	xCHECK(list.Front() == "dog")
//	xCHECK(list.Back() == "bird")
//	list.Remove(list.Begin()++);
//	xCHECK(list.Size() == 1);
//	xCHECK(list.Front() == "bird")
//	xCHECK(list.Back() == "bird")
//	n = 0;
//	for (xStringList::Iterator it = list.Begin(); it != list.End(); ++it)
//		n++;
//	xCHECK(n == 1)
//	list.Remove(list.Begin()++);
//	xCHECK(list.Size() == 0)
//	n = 0;
//	for (xStringList::Iterator it = list.Begin(); it != list.End(); ++it)
//		n++;
//	xCHECK(n == 0)
//	list.AddBack("dog");
//	list.AddBack("cat");
//	list.AddBack("bird");
//	xStringList::Iterator it = list.Begin();	
//	xStringList::Iterator it1 = ++it;
//	xCHECK((*it1) == "cat")
//	xStringList::Iterator it2 = it++;
//	xCHECK((*it2) == "cat")
//	xCHECK((*it) == "bird")
//	list.Clear();
//	xCHECK(list.Size() == 0)*/
//}