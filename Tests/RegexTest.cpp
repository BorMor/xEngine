#include "Prerequisites.h"

xTEST(Regex)
{
	{
		xString str = "Попробуем 12.11.2008 найти 12.03.2008 тут 12.03.2002 дату"; 
		xMatchCollection matches;
		xCHECK(xRegex::Matches(str, "\\d{2}\\.\\d{2}\\.\\d{4}", matches));
		xCHECK(matches.Count() == 3);
		xCHECK(matches[0].Value() == "12.11.2008");
		xCHECK(matches[0].Index() == 10);
		xCHECK(matches[0].Length() == 10);
		xCHECK(matches[1].Value() == "12.03.2008");
		xCHECK(matches[2].Value() == "12.03.2002");
	}

	{
		xString str = xRegex::Replace("abcd /*efgh */ ijkl", "/\\*[\\s\\w]*\\*/", "");
		xCHECK(str == "abcd  ijkl");
	}

	{
		xString str = "The the quick brown fox  fox jumped over the lazy dog dog."; 
		xMatchCollection matches;
		xCHECK(xRegex::Matches(str, "\\b(?<word>\\w+)\\s+(\\k<word>)\\b", matches, xRegexOptions::IgnoreCase));
		xCHECK(matches.Count() == 3);
		xCHECK(matches[0].Value() == "The the");
		xCHECK(matches[1].Value() == "fox  fox");
		xCHECK(matches[1].Groups.Count() == 2);
		xCHECK(matches[1].Groups[0].Value() == "fox");
		xCHECK(matches[2].Value() == "dog dog");
	}

	{
		xRegex regex("\\d{1,2}\\.\\d{2}\\.\\d{2,4}");
		xMatch match;
		xCHECK(!regex.Match("asd", match));
		xCHECK(!regex.IsMatch("asdf"));
		xCHECK(match.Success() == false);
		xCHECK(regex.IsMatch("1.06.1984") == true);
		xCHECK(regex.IsMatch("12.06.84") == true);
		xCHECK(regex.IsMatch("12.06.abcd") == false);
	}
}