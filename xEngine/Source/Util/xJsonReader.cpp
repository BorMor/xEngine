#include "xEngine.h"
#include "xJsonReader.h"

xJsonReader::xJsonReader(const char* source, xString* error, xUInt32* line, xUInt32* pos)
	: mStart(source), mCurrent(source), mErrorMessage(error), mErrLine(line), mErrPos(pos)
{
	mEnd = mStart + strlen(source);
}

xJsonReader::~xJsonReader()
{
}

bool xJsonReader::ReadValue(xJsonValue& value)
{
	xJsonTokenType::Enum token;
	if (ReadToken(token))
	{
		switch (token)
		{
		case xJsonTokenType::EndOfStream:
			return false;
		case xJsonTokenType::ObjectBegin:
			return ReadObject(value);
		case xJsonTokenType::ArrayBegin:
			return ReadArray(value);
		case xJsonTokenType::String:
			return ReadString(value);			
		case xJsonTokenType::Number:
			return ReadNumber(value);
		case xJsonTokenType::Boolean:
			return ReadBoolean(value);
		case xJsonTokenType::Null:
			return ReadNull(value);
		default:
			SetError("Unexpected character.");
			return false;
		}
	}
	else
	{
		SetError("Unexpected character.");
		return false;
	}
	return true;
}
	
bool xJsonReader::ReadObject(xJsonValue& value)
{
	enum State
	{
		Name,
		Colon,
		Value,
		CommaOrEnd
	};
		
	value.SetType(xJsonType::Object);

	State state = Name;		
	xString		name;

	xJsonTokenType::Enum token;
	while (true)
	{
		if (!ReadToken(token))
			return false;
		if (state == Name)
		{
			if (token == xJsonTokenType::String)
			{
				if (!ReadString(name))
					return false;
				state = Colon;
			}
			else
			{
				SetError("'\"' expected.");
				return false;
			}
		}
		else if (state == Colon)
		{
			if (token == xJsonTokenType::MemberSeparator)
				state = Value;
			else
			{
				SetError("':' expected.");
				return false;
			}
		}
		else if (state == Value)
		{
			ReturnToken();
				
			xJsonValue* val = new xJsonValue();
			if (!ReadValue(*val))
			{
				delete val;
				return false;
			}
			value.Add(name, val);
			state = CommaOrEnd;			
			name = "";
		}
		else if (state == CommaOrEnd)
		{
			if (token == xJsonTokenType::ArraySeparator)
				state = Name;
			else if (token == xJsonTokenType::ObjectEnd)
				break;
			else
			{
				SetError("',' or '}' expected.");
				return false;
			}
		}
	}
	return true;
}

bool xJsonReader::ReadArray(xJsonValue& value)
{
	enum State
	{
		Value,
		CommaOrEnd
	};

	value.SetType(xJsonType::Array);
	
	State state = Value;

	xJsonTokenType::Enum token;
	while (true)
	{
		if (!ReadToken(token))
			return false;
		if (state == Value)
		{
			ReturnToken();
			xJsonValue* val = new xJsonValue();
			if (!ReadValue(*val))
			{
				delete val;
				return false;
			}

			value.Add(val);
			state = CommaOrEnd;
		}
		else if (state == CommaOrEnd)
		{
			if (token == xJsonTokenType::ArraySeparator)
				state = Value;
			else if (token == xJsonTokenType::ArrayEnd)
				break;
			else
			{
				SetError("',' or ']' expected.");
				return false;
			}
		}
	}
	return true;
}

bool xJsonReader::ReadBoolean(xJsonValue& value)
{
	ReturnToken();
	if (Match("true"))
	{
		value = xJsonValue(true);
		return true;
	}
	else if (Match("false"))
	{
		value = xJsonValue(false);
		return true;
	}
	return false;
}

bool xJsonReader::ReadNull(xJsonValue& value)
{
	ReturnToken();
	if (Match("null"))
	{
		value = xJsonValue(xJsonType::Null);
		return true;	
	}
	return false;
}

#define IS_DIGIT(c) (c >= '0' && c <= '9')

bool xJsonReader::ReadNumber(xJsonValue& value)
{
	ReturnToken();
	const xChar* begin = mCurrent;
	const xChar* end = begin;
	while (*end && ((*end >= '0' && *end <= '9') || *end == 'e' || *end == 'E' || *end == '-' || *end == '+' || *end == '.'))
		end++;


	bool valid = true;

	bool negative = false;
	xUInt32 integer = 0;
	bool is_double = false;	
	double fraction = 0.0;
	bool exponent_negative = false;
	xUInt32 exponent = 0;
	xUInt32 power_of_ten = 0;

	// sign
	if (mCurrent < mEnd && *mCurrent == '-')
	{
		negative = true;
		mCurrent++;
	}	

	// integer part
	if (mCurrent < mEnd)
	{
		if (*mCurrent != '0')
		{
			if (!IS_DIGIT(*mCurrent))
				valid = false;

			for (; mCurrent < mEnd && IS_DIGIT(*mCurrent); ++mCurrent)
				integer = integer * 10 + (*mCurrent - '0');
		}
		else
			mCurrent++;
	}
	
	if (valid)
	{
		// fraction part
		if (mCurrent < mEnd && *mCurrent == '.')
		{
			is_double = true;		
			++mCurrent;
		
			if (!IS_DIGIT(*mCurrent))
				valid = false;

			float inv_base = 1;
			for (; mCurrent < mEnd && IS_DIGIT(*mCurrent); ++mCurrent)
			{
				inv_base *= float(0.1);
				fraction += (*mCurrent - '0') * inv_base;
			}
		}

		if (valid)
		{
			// exponent				
			if (mCurrent < mEnd && (*mCurrent == 'e' || *mCurrent == 'E'))
			{
				++mCurrent;

				if (*mCurrent == '-')
				{
					exponent_negative = true;
					++mCurrent;
				}
				else if (*mCurrent == '+')
					++mCurrent;

				if (!IS_DIGIT(*mCurrent))
					valid = false;
				for (; mCurrent < mEnd && IS_DIGIT(*mCurrent); ++mCurrent)
					exponent = 10 * exponent + (*mCurrent - '0');
			}
			
			if (exponent)
			{
				is_double = true;
				power_of_ten = 10;
				for (; exponent > 1; exponent--)
					power_of_ten *= 10;
			}
		}
	}

	if (valid && mCurrent != end)
		valid = false;

	if (!valid)
	{
		SetError(xString::Format("'%s' is invalid number.", xString(begin, end-begin).c_str()));
		return false;
	}

	if (is_double)
	{
		double result = (double)integer + fraction;
		if (negative)
			result *= -1.0;
		if (exponent)
		{
			if (exponent_negative)
				result /= (double)power_of_ten;
			else
				result *= (double)power_of_ten;
		}
		value = xJsonValue(result);
	}
	else
	{
		if (negative)
			value = xJsonValue((xInt32)integer * -1);
		else
			value = xJsonValue(integer);
	}
	return true;
}

bool xJsonReader::ReadString(xJsonValue& value)
{
	xString string;
	if (!ReadString(string))
		return false;
	value = xJsonValue(string);
	return true;
}

void xJsonReader::SetError(const xString& message)
{
	xUInt32	pos = 0;
	xUInt32 line = 1;
	bool err_line = true;
	for (const xChar* c = mCurrent; c != mStart; --c)
	{
		if (*c == '\n')
		{
			err_line = false;
			++line;
		}
		else 
		{
			if (err_line)
				++pos;
		}
	}
	if (mErrorMessage)
		mErrorMessage->Set(message);
	if (mErrLine)
		*mErrLine = line;
	if (mErrPos)
		*mErrPos = pos;
}

void xJsonReader::SkipWhiteSpaceAndComments()
{
	while (true)
	{
		if (!*mCurrent)
			break;
		if (*mCurrent == '\x20' || *mCurrent == '\x9' || *mCurrent == '\xD' || *mCurrent == '\xA')
			++mCurrent;
		else
		{
			if (*mCurrent == '/' && *(mCurrent+1) == '/')
			{
				while (mCurrent < mEnd && *mCurrent++ != '\n')
				{
				}
			}
			else if (*mCurrent == '/' && *(mCurrent+1) == '*')
			{				
				if (mCurrent+3 < mEnd)
				{
					mCurrent += 3;
					while (mCurrent < mEnd)
					{
						if (*(mCurrent-1) == '*' && *mCurrent++ == '/')
							break;
						mCurrent++;
					}					
				}
				else
					mCurrent += 2;				
			}
			else
				break;
		}
	}
}

void xJsonReader::ReturnToken()
{
	mCurrent--;
}

bool xJsonReader::ReadToken(xJsonTokenType::Enum& token)
{
	SkipWhiteSpaceAndComments();
	if (mCurrent < mEnd)
	{
		switch (*mCurrent++)
		{
		case '{':
			token = xJsonTokenType::ObjectBegin;
			break;
		case '}':
			token = xJsonTokenType::ObjectEnd;
			break;
		case '[':
			token = xJsonTokenType::ArrayBegin;
			break;
		case ']':
			token = xJsonTokenType::ArrayEnd;
			break;
		case '"':
			token = xJsonTokenType::String;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '-':
			token = xJsonTokenType::Number;
			break;
		case 't':
		case 'f':
			token = xJsonTokenType::Boolean;
			break;
		case 'n':
			token = xJsonTokenType::Null;
			break;
		case ',':
			token = xJsonTokenType::ArraySeparator;
			break;
		case ':':
			token = xJsonTokenType::MemberSeparator;
			break;
		default:
			SetError("Unexpected character.");
			return false;
		}
	}
	else
		token = xJsonTokenType::EndOfStream;

	return true;
}

bool xJsonReader::Match(const xChar* pattern)
{
	const xChar* c = pattern;
	do
	{
		if (*c != *mCurrent++)
		{
			SetError(xString::Format("'%s' expected.", pattern).c_str());
			return false;
		}
	} while (*++c);
	return true;
}

static xString xUnicodeCodePointToUTF8(xUInt32 cp)
{
	xString result;
	if (cp <= 0x7f) 
		result.Append((xChar)(cp));
	else if (cp <= 0x7FF) 
	{
		result.Append((xChar)(0x80 | (0x3f & cp)));
		result.Append((xChar)(0xC0 | (0x1f & (cp >> 6))));
	} 
	else if (cp <= 0xFFFF) 
	{
		result.Append((xChar)(0x80 | (0x3f & cp)));
		result.Append((xChar)(0x3f & (cp >> 6)));
		result.Append((xChar)(0xf & (cp >> 12)));
	}
	else if (cp <= 0x10FFFF) 
	{
		result.Append((xChar)(0x80 | (0x3f & cp)));
		result.Append((xChar)(0x80 | (0x3f & (cp >> 6))));
		result.Append((xChar)(0x80 | (0x3f & (cp >> 12))));
		result.Append((xChar)(0xF0 | (0x7 & (cp >> 18))));
	} 

	return result;
}

bool xJsonReader::DecodeUnicodeCodePoint(xUInt32& unicode)
{
	if (!DecodeUnicodeEscapeSequence(unicode))
		return false;
	if (unicode >= 0xD800 && unicode <= 0xDBFF)
	{
		// surrogate pairs
		if (mEnd - mCurrent < 6)
		{
			SetError( "Additional six characters expected to parse unicode surrogate pair.");
			return false;
		}
		unsigned int surrogate;
		if (*(mCurrent++) == '\\' && *(mCurrent++)== 'u')
		{
			if (DecodeUnicodeEscapeSequence(surrogate))
				unicode = 0x10000 + ((unicode & 0x3FF) << 10) + (surrogate & 0x3FF);
			else
				return false;
		} 
		else
		{
			SetError("Expecting another \\u token to begin the second half of a unicode surrogate pair.");
			return false;
		}
	}
	return true;
}

bool xJsonReader::DecodeUnicodeEscapeSequence(xUInt32& unicode)
{
	if (mEnd - mCurrent < 4)
	{
		SetError("Bad unicode escape sequence in string: four digits expected.");
		return false;
	}
   unicode = 0;
   for (size_t i = 0; i < 4; ++i)
   {
      xChar c = *mCurrent++;
      unicode *= 16;
      if (c >= '0' && c <= '9')
         unicode += c - '0';
      else if (c >= 'a' &&  c <= 'f')
         unicode += c - 'a' + 10;
      else if (c >= 'A' &&  c <= 'F')
         unicode += c - 'A' + 10;
      else
	  {
         SetError("Bad unicode escape sequence in string: hexadecimal digit expected.");
		 return false;
	  }
   }
   return true;
}

bool xJsonReader::ReadString(xString& string)
{
	const xChar* first = mCurrent;
		
	while (true)
	{
		if (!*mCurrent)
		{
			SetError("EOF reached, while expected '\"'");
			return false;
		}
		else if (*(unsigned char*)mCurrent < '\x20')
		{
			SetError("Control characters not allowed in strings");
			return false;
		}
		else if (*mCurrent == '\\')
		{
			if (*++mCurrent == 0)
			{
				SetError("Empty escape sequence in string");
				return false;
			}
			xChar escape = *mCurrent++;
			switch (escape)
			{
			case '"':
				string.Append('"');
				break;
			case '/':
				string.Append('/');
				break;
			case '\\':
				string.Append('\\');
				break;
			case 'b':
				string.Append('\b');
				break;
			case 'f':
				string.Append('\f');
				break;
			case 'n':
				string.Append('\n');
				break;
			case 'r':
				string.Append('\r');
				break;
			case 't':
				string.Append('\t');
				break;
			case 'u':
				{
					xUInt32 cp;
					if (!DecodeUnicodeCodePoint(cp))
						return false;
					string.Append(xUnicodeCodePointToUTF8(cp));
				}
				break;
			default:
				SetError("Bad escape sequence in string");
				return false;
			}
		}
		else if (*mCurrent == '"')
		{						
			++mCurrent;
			break;
		}
		else
			string.Append(*mCurrent++);
	}
	return true;
}