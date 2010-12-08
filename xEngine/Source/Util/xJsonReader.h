#pragma once

struct xJsonTokenType
{
	enum Enum
	{
		EndOfStream = 0,
		ObjectBegin,
		ObjectEnd,
		ArrayBegin,
		ArrayEnd,
		String,
		Number,
		Boolean,
		Null,
		ArraySeparator,
		MemberSeparator,
	};
};

class xJsonReader
{
public:
	xJsonReader(const char* source, xString* error = 0, xUInt32* line = 0, xUInt32* pos = 0);
	~xJsonReader();
	
	bool ReadValue(xJsonValue& value);
	bool ReadObject(xJsonValue& value);
	bool ReadArray(xJsonValue& value);
	bool ReadBoolean(xJsonValue& value);
	bool ReadNull(xJsonValue& value);
	bool ReadNumber(xJsonValue& value);
	bool ReadString(xJsonValue& string);
protected:
	const xChar*	mStart;
	const xChar*	mEnd;
	const xChar*	mCurrent;
	xString*		mErrorMessage;
	xUInt32*		mErrLine;
	xUInt32*		mErrPos;

	void SetError(const xString& message);
	bool Match(const xChar* pattern);
	bool DecodeUnicodeCodePoint(xUInt32& cp);
	bool DecodeUnicodeEscapeSequence(xUInt32& unicode);
	bool ReadString(xString& string);
	void SkipWhiteSpaceAndComments();
	void ReturnToken();
	bool ReadToken(xJsonTokenType::Enum& token);
};
