#include "Prerequisites.h"

xTEST(Array)
{
	{
		xArray<int> arr;
		for (size_t i = 0; i < 30; i++)
			arr.AddBack(i);
		xCHECK(arr.Capacity() >= arr.Size());
		xCHECK(arr.Size() == 30);
		size_t capacity = arr.Capacity();

		int sum1 = 0;
		for (size_t i = 0; i < arr.Size(); i++)
			sum1 += arr[i];

		int sum2 = 0;		
		for (auto it = arr.Begin(); it != arr.End(); ++it)
			sum2 += *it;
		xCHECK(sum1 == sum2);
		xCHECK(sum1 == 435);
		arr.Clear();
		xCHECK(arr.Capacity() == capacity);
		xCHECK(arr.Size() == 0);
	}
	{
		xArray<xString> arr;
		arr.AddBack("ab");
		arr.AddBack("cd");
		auto it = arr.Find("cd");
		arr.InsertAfter(it, "01");
		arr.AddBack("ef");
		it = arr.Find("cd");
		arr.InsertBefore(it, "23");
		xCHECK(arr[1] == "23")
		xString s;
		for (auto it = arr.Begin(); it != arr.End(); ++it)
			s += *it;
		xCHECK(s == "ab23cd01ef");
	}
	{
		xArray<int> arr(10);
		arr[0] = 0;
		arr[9] = 9;
		xCHECK(arr.Size() == 10);
	}
	{
		xArray<char> arr;
		arr.AddBack('1');
		arr.AddBack('2');
		arr.AddBack('3');
		arr.AddBack('4');
		auto it = arr.Find('3');
		arr.InsertAfter(it, '5');
		it = arr.Find('4');
		arr.InsertAfter(it, '6');
		xCHECK(arr.Size() == 6);
		arr.InsertAfter(arr.Begin(), '0');
		arr.InsertBefore(arr.Begin(), '9');
		it = arr.Find('6');
		arr.InsertBefore(it, '8');
		xString str;
		for (auto it = arr.Begin(); it != arr.End(); ++it)
			str += *it;
		xCHECK(str == "910235486");
		str = "";
		it = arr.Find('3');
		arr.Remove(it);
		for (auto it = arr.Begin(); it != arr.End(); ++it)
			str += *it;
		xCHECK(arr.Size() == 8); 
		xCHECK(str == "91025486");
	}
}