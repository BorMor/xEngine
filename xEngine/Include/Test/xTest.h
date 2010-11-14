#pragma once

#include "xTestListener.h"

class xEXPORT xTest
{
public:
	xTest(const char* name, const char* filename, int line);
	virtual ~xTest();

	const xString& Name() const;
	void Run(xTestListener*);	
protected:
	virtual void RunTest (xTestListener*) = 0;    
    
    xString mName;
    xString mFilename;
    int		mLine;
};

#include "xTestRegistry.h"

#define xTEST(name)																\
class name##Test : public xTest													\
{																				\
public:																			\
	name##Test() : xTest(#name"Test", __FILE__, __LINE__)						\
	{																			\
	}																			\
protected:																		\
	void RunTest(xTestListener* listener);										\
} name##TestInstance;															\
																				\
void name##Test::RunTest(xTestListener* listener)								\

#define xCHECK(condition)														\
{																				\
	try																			\
	{																			\
		if (!(condition))														\
			listener->AddFailure(#condition, mName.c_str(), __FILE__, __LINE__);\
	}																			\
	catch(...)																	\
	{																			\
	}																			\
}

//ExceptionHandler::Handle(result_, #condition, m_name, __FILE__, __LINE__); \

/*																			\*/