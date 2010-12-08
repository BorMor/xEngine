#pragma once

struct xJsonType
{
	enum Enum
	{
		Null,
		Boolean,
		Int32,
		UInt32,
		Double,
		String,		
		Object,
		Array,
	};
};

class xEXPORT xJsonValue
{
	typedef xMap<xString, xJsonValue*> ObjectValues;
	typedef xArray<xJsonValue*> ArrayValues;
public:
	xJsonValue(xJsonType::Enum type = xJsonType::Null);
	xJsonValue(bool value);	
	xJsonValue(xInt32 value);
	xJsonValue(xUInt32 value);
	xJsonValue(xDouble value);
	xJsonValue(const xChar* value);
	xJsonValue(const xString& value);

	xJsonValue(const xJsonValue& other);
	~xJsonValue();

	xJsonValue& operator =(const xJsonValue& other);

	void SetType(xJsonType::Enum type);
	xJsonType::Enum Type() const;

	bool IsNull() const;
	bool IsBool() const;
	bool IsInt32() const;
	bool IsUInt32() const;
	bool IsDouble() const;
	bool IsString() const;		
	bool IsObject() const;
	bool IsArray() const;

	bool AsBool() const;	
	xInt32 AsInt32() const;
	xUInt32 AsUInt32() const;
	xDouble AsDouble() const;
	xFloat AsFloat() const;	
	xString AsString() const;


	xJsonValue& operator [](size_t index);
	const xJsonValue& operator [](size_t index) const;
	
	xJsonValue& operator [](const char* name);
	const xJsonValue& operator [](const char* name) const;

	void Add(const xString& key, xJsonValue* value);
	void Add(xJsonValue* value);

	size_t Size() const;

	static xJsonValue Null;
protected:
	xJsonType::Enum	mType;
	union
    {
		bool			AsBool;
        xInt32			AsInt;
        xUInt32			AsUInt;
        xDouble			AsDouble;        
		xString*		AsString;
	    ObjectValues*	AsObject;
		ArrayValues*	AsArray;
    } mValue;

	void CopyFrom(const xJsonValue& other);
};

class xEXPORT xJson
{
public:
	static bool Parse(const xString& string, xJsonValue& value, xString* error = 0, xUInt32* line = 0, xUInt32* pos = 0);
};