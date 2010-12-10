#include "xEngine.h"
#define PCRE_STATIC 1
#include <pcre.h>

#define OFFSET_COUNT 30

struct xRegex::Impl
{
	pcre*	mCompiledPattern;
};

xRegex::xRegex(const xString& pattern, xRegexOptions::Flags options)
{
	pImpl = new Impl;

	const char* error;
	int   erroffset;
	int	opts = 0;
	if (options && xRegexOptions::Multiline)
		opts |= PCRE_MULTILINE;
	if (options & xRegexOptions::IgnoreCase)
		opts |= PCRE_CASELESS;
	
	pImpl->mCompiledPattern = pcre_compile(pattern.c_str(), opts,  &error, &erroffset, 0);
}

xRegex::~xRegex()
{
	if (pImpl->mCompiledPattern)
		pcre_free(pImpl->mCompiledPattern);
	xSAFE_DELETE(pImpl);
}

bool xRegex::IsMatch(const xString& input)
{
	if (pImpl->mCompiledPattern)
	{
		int offsets[3];
		if (pcre_exec(pImpl->mCompiledPattern, 0, input.c_str(), input.Length(), 0, 0, offsets, 3) > 0)
			return true;
	}

	return false;
}

bool xRegex::Match(const xString& input, xMatch& match)
{
	bool result = false;
	if (pImpl->mCompiledPattern)
	{	
		int offsets[OFFSET_COUNT];
			
		int rc = pcre_exec(pImpl->mCompiledPattern, 0, input.c_str(), 0, input.Length(), 0, offsets, OFFSET_COUNT);          
		if (rc > 0)
		{
			if (!result)
				match.Groups.mGroups.Clear();
			result = true;
			match.mSuccess = true;
			for (int i = 0; i < rc; i++)
			{
				xGroup* group;
				if (i == 0)
					group = &match;
				else
					group = new xGroup();
						
				group->mIndex = offsets[2*i];
				group->mLength = offsets[2*i+1] - offsets[2*i];
				group->mValue.Set(input.c_str() + offsets[2*i], offsets[2*i+1] - offsets[2*i]);

				if (i > 0)
					match.Groups.mGroups.AddBack(group);
			}
		}
	}
	
	return result;
}

bool xRegex::Matches(const xString& input, xMatchCollection& matches)
{
	bool result = false;
	if (pImpl->mCompiledPattern)
	{	
		int offsets[OFFSET_COUNT];

		unsigned int offset = 0;
		unsigned int len = input.Length();
			
		while (offset < len)
		{
			int rc = pcre_exec(pImpl->mCompiledPattern, 0, input.c_str(), len, offset, 0, offsets, OFFSET_COUNT);          
			if (rc > 0)
			{
				if (!result)
					matches.mMatches.Clear();
				result = true;
				xMatch* match = new xMatch();
				match->mSuccess = true;
				for (int i = 0; i < rc; i++)
				{
					xGroup* group;
					if (i == 0)
						group = match;
					else
						group = new xGroup();
						
					group->mIndex = offsets[2*i];
					group->mLength = offsets[2*i+1] - offsets[2*i];
					group->mValue.Set(input.c_str() + offsets[2*i], offsets[2*i+1] - offsets[2*i]);

					if (i > 0)
						match->Groups.mGroups.AddBack(group);
				}
				matches.mMatches.AddBack(match);
				offset = offsets[1];
			}
			else
				break;
			
		}
	}
	
	return result;
}

xString xRegex::Replace(const xString& input, const xString replacement)
{
	xString result;
	if (pImpl->mCompiledPattern)
	{	
		int offsets[OFFSET_COUNT];

		unsigned int offset = 0;
		unsigned int len = input.Length();
	
		while (offset < len)
		{
			int rc = pcre_exec(pImpl->mCompiledPattern, 0, input.c_str(), len, offset, 0, offsets, OFFSET_COUNT);          
			if (rc > 0)
			{
				const char* s1 = input.c_str() + offset;
				result += xString(input.c_str() + offset, offsets[0] - offset) + replacement;
				offset = offsets[1];
			}
			else
			{
				result += xString(input.c_str() + offset, len - offset);
				break;
			}
			
		}
	}
	return result;
}

bool xRegex::IsMatch(const xString& input, const xString& pattern, xRegexOptions::Flags options)
{
	return xRegex(pattern, options).IsMatch(input);
}

bool Match(const xString& input, const xString& pattern, xMatch& match, xRegexOptions::Flags options)
{
	return xRegex(pattern, options).Match(input, match);
}

bool xRegex::Matches(const xString& input, const xString& pattern, xMatchCollection& matches, xRegexOptions::Flags options)
{	
	return xRegex(pattern, options).Matches(input, matches);
}

xString xRegex::Replace(const xString& input, const xString& pattern, const xString replacement, xRegexOptions::Flags options)
{
	return xRegex(pattern, options).Replace(input, replacement);
}