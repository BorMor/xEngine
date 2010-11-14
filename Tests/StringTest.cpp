#include "Prerequisites.h"

xTEST(String)
{
	{
		xString str;
		xCHECK(str.Length() == 0);
		xCHECK(sizeof(xString) == 32);
		str = "abc";
		xCHECK(str.Length() == 3);
		xCHECK(strcmp(str.c_str(), "abc") == 0);
	}
	{
		xString str1 = "abc";
		xString str2 = "abc";
		xString str3 = "a";
		
		xCHECK(str1 == str2);
		xCHECK(str1 != str3);
		str3 += 'b';
		xCHECK(str3 == "ab");
		str3 += "c";
		xCHECK(str3 == str1);
		xCHECK(str3[1] == 'b');
	}
	{
		xCHECK(xString::Format("%dx%d", 12, 23) == "12x23");
	}
}