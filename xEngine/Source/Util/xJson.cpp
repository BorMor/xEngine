#include "xEngine.h"
#include "xJsonReader.h"

xJsonValue xJsonValue::Null;

xJsonValue::xJsonValue(xJsonType::Enum type)
	: mType(xJsonType::Null)
{
	SetType(type);	
}

xJsonValue::xJsonValue(bool value)
	: mType(xJsonType::Boolean)
{
	mValue.AsBool = value;
}

xJsonValue::xJsonValue(xInt32 value)
	: mType(xJsonType::Int32)
{
	mValue.AsInt = value;
}

xJsonValue::xJsonValue(xUInt32 value)
	: mType(xJsonType::UInt32)
{
	mValue.AsUInt = value;
}

xJsonValue::xJsonValue(xDouble value)
	: mType(xJsonType::Double)
{
	mValue.AsDouble = value;
}

xJsonValue::xJsonValue(const xChar* value)
	: mType(xJsonType::String)
{
	mValue.AsString = new xString(value);
}

xJsonValue::xJsonValue(const xString& value)
	: mType(xJsonType::String)
{
	mValue.AsString = new xString(value);
}

xJsonValue::xJsonValue(const xJsonValue& other)
{
	CopyFrom(other);	
}

xJsonValue::~xJsonValue()
{
	switch (mType)
	{
	case xJsonType::String:
		delete mValue.AsString;
		break;
	case xJsonType::Object:
		for (ObjectValues::Iterator it = mValue.AsObject->Begin(); it != mValue.AsObject->End(); ++it)
			delete it->Value();
		mValue.AsObject->Clear();
		delete mValue.AsObject;
		break;
	case xJsonType::Array:
		for (ArrayValues::Iterator it = mValue.AsArray->Begin(); it != mValue.AsArray->End(); ++it)
			delete *it;
		mValue.AsArray->Clear();
		delete mValue.AsArray;
		break;
	};
}

xJsonValue& xJsonValue::operator = (const xJsonValue& other)
{
	if (this != &Null)
	{
		this->~xJsonValue();
		CopyFrom(other);
	}
	return *this;
}

void xJsonValue::SetType(xJsonType::Enum type)
{
	if (this != &Null)
	{
		if (mType != xJsonType::Null)
			this->~xJsonValue();
		mType = type;
		switch (mType)
		{
		case xJsonType::String:
			mValue.AsString = new xString();
			break;
		case xJsonType::Object:
			mValue.AsObject = new ObjectValues();
			break;
		case xJsonType::Array:
			mValue.AsArray = new ArrayValues();
			break;
		};
	}
}

xJsonType::Enum xJsonValue::Type() const
{
	return mType;
}

bool xJsonValue::IsNull() const
{
	return mType == xJsonType::Null;
}

bool xJsonValue::IsBool() const
{
	return mType == xJsonType::Boolean;
}

bool xJsonValue::IsInt32() const
{
	return mType == xJsonType::Int32;
}

bool xJsonValue::IsUInt32() const
{
	return mType == xJsonType::UInt32;
}

bool xJsonValue::IsDouble() const
{
	return mType == xJsonType::Double;
}

bool xJsonValue::IsString() const
{
	return mType == xJsonType::String;
}

bool xJsonValue::IsObject() const
{
	return mType == xJsonType::Object;
}

bool xJsonValue::IsArray() const
{
	return mType == xJsonType::Array;
}

bool xJsonValue::AsBool() const
{
	switch (mType)
	{
	case xJsonType::Boolean:
		return mValue.AsBool;
	case xJsonType::Int32:
		return mValue.AsInt != 0;
	case xJsonType::UInt32:
		return mValue.AsUInt != 0;
	case xJsonType::Double:
		return mValue.AsDouble != 0.0;
	}
	return false;
}

xInt32 xJsonValue::AsInt32() const
{
	switch (mType)
	{
	case xJsonType::Boolean:
		return mValue.AsBool == true ? 1 : 0;
	case xJsonType::Int32:
		return mValue.AsInt;
	case xJsonType::UInt32:
		return (xInt32)mValue.AsUInt;
	case xJsonType::Double:
		return (xInt32)mValue.AsDouble;
	}
	return 0;
}

xUInt32 xJsonValue::AsUInt32() const
{
	switch (mType)
	{
	case xJsonType::Boolean:
		return mValue.AsBool == true ? 1 : 0;
	case xJsonType::Int32:
		return (xUInt32)mValue.AsInt;
	case xJsonType::UInt32:
		return mValue.AsUInt;
	case xJsonType::Double:
		return (xUInt32)mValue.AsDouble;
	}
	return 0;
}

xDouble xJsonValue::AsDouble() const
{
	switch (mType)
	{
	case xJsonType::Boolean:
		return mValue.AsBool == true ? 1.0 : 0.0;
	case xJsonType::Int32:
		return (xDouble)mValue.AsInt;
	case xJsonType::UInt32:
		return (xDouble)mValue.AsUInt;
	case xJsonType::Double:
		return mValue.AsDouble;
	}
	return 0.0;
}

xFloat xJsonValue::AsFloat() const
{
	return (xFloat)AsDouble();
}

xString xJsonValue::AsString() const
{
	switch (mType)
	{
	case xJsonType::Boolean:
		return mValue.AsBool == true ? "true" : "false";
	case xJsonType::String:
		return *mValue.AsString;
	}
	return "";
}

xJsonValue& xJsonValue::operator [](size_t index)
{	
	if (mType == xJsonType::Array && index < mValue.AsArray->Size())
		return *(*mValue.AsArray)[index];
	return Null;
}

const xJsonValue& xJsonValue::operator [](size_t index) const
{
	if (mType == xJsonType::Array && index < mValue.AsArray->Size())
		return *(*mValue.AsArray)[index];
	return Null;
}
	
xJsonValue& xJsonValue::operator [](const char* name)
{
	if (mType == xJsonType::Object)
	{
		ObjectValues::Iterator it = mValue.AsObject->Find(name);
		if (it != mValue.AsObject->End())
			return *it->Value();
	}
	return Null;
}

const xJsonValue& xJsonValue::operator [](const char* name) const
{
	if (mType == xJsonType::Object)
	{
		ObjectValues::Iterator it = mValue.AsObject->Find(name);
		if (it != mValue.AsObject->End())
			return *it->Value();
	}

	return Null;
}

void xJsonValue::Add(const xString& key, xJsonValue* value)
{
	if (mType == xJsonType::Object)
		mValue.AsObject->Insert(key, value);
}

void xJsonValue::Add(xJsonValue* value)
{
	if (mType == xJsonType::Array)
		mValue.AsArray->AddBack(value);
}

size_t xJsonValue::Size() const
{
	switch (mType)
	{
	case xJsonType::Object:
		return mValue.AsObject->Size();
	case xJsonType::Array:
		return mValue.AsArray->Size();
	}
	return 0;
}

void xJsonValue::CopyFrom(const xJsonValue& other)
{
	mType = other.mType;
	switch (mType)
	{
	case xJsonType::Null:
	case xJsonType::Boolean:
	case xJsonType::Int32:
	case xJsonType::UInt32:
	case xJsonType::Double:
		mValue = other.mValue;
		break;
	case xJsonType::String:		
		mValue.AsString = new xString(*other.mValue.AsString);
		break;
	case xJsonType::Object:	
		mValue.AsObject = new ObjectValues();
		for (ObjectValues::Iterator it = other.mValue.AsObject->Begin(); it != other.mValue.AsObject->End(); ++it)
			mValue.AsObject->Insert(it->Key(), new xJsonValue(*it->Value()));
		break;
	case xJsonType::Array:
		mValue.AsArray = new ArrayValues();
		for (ArrayValues::Iterator it = other.mValue.AsArray->Begin(); it != other.mValue.AsArray->End(); ++it)
			mValue.AsArray->AddBack(new xJsonValue(*(*it)));
		break;
	}
}

bool xJson::Parse(const xString& string, xJsonValue& value, xString* error, xUInt32* line, xUInt32* pos)
{	
	xJsonReader reader(string.c_str(), error, line, pos);
	return reader.ReadValue(value);
}