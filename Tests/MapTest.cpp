#include "Prerequisites.h"

xTEST(Map)
{
	typedef xMap<xString, int> xTestMap;
	xTestMap map;
	
	xCHECK(map.Size() == 0)
	xCHECK(map.IsEmpty())
	map.Insert("test", 123);
	map.Insert("abc", 256);
	xCHECK(map.Size() == 2)
	map.Insert("qwerty", 8);
	xCHECK(!map.IsEmpty())
	xCHECK(map["abc"] == 256)

	int sum = 0;
	for (xTestMap::Iterator it = map.Begin(); it != map.End(); ++it)
		sum += it->Value();
	xCHECK(sum == (123 + 256 + 8))
	
	xTestMap map2(map);

	xCHECK(map.Contains("abc") == true)
	map.Remove("abc");
	xCHECK(map.Contains("abc") == false)

	sum = 0;
	for (xTestMap::Iterator it = map2.Begin(); it != map2.End(); ++it)
		sum += it->Value();
	xCHECK(sum == (123 + 256 + 8))
}