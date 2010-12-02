#pragma once

#include <exception>

class xEXPORT xException : public std::exception
{
	typedef	std::exception BaseClass;
public:
	xException(const xString& source, const xString& description, const char* file, long line);
	xException();

	const xString& Message() const;
	virtual const char* what() const throw();

	virtual xString Type() const;
protected:
	xString mSource;
	xString mDescription;
	xString	mFile;
	xUInt32	mLine;
	mutable xString	mFullDescription;

	void PrepareMessage() const;	
};


#define xTHROW(exception, src, description) throw exception(src, description, __FILE__, __LINE__);

#define xDECLARE_EXCEPTION(T, BASE)																								\
class xEXPORT T : public BASE									\
{												\
public:												\
	T(const xString& source, const xString& description, const char* file, long line);	\
	T();											\
												\
	xString Type() const;									\
};

#define xIMPLEMENT_EXCEPTION(T, BASE)							\
T::T(const xString& source, const xString& description, const char* file, long line)	\
	: BASE(source, description, file, line)						\
{											\
}											\
											\
T::T()											\
{											\
}											\
											\
xString T::Type() const									\
{											\
	return xString(#T);								\
}

xDECLARE_EXCEPTION(xFileNotFoundException, xException)	
xDECLARE_EXCEPTION(xInvalidOperationException, xException)
	