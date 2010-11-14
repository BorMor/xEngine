#include "xEngine.h"
#include "Test/xTest.h"
#include "Test/xTestRegistry.h"

xTest::xTest(const char* name, const char* filename, int line)
	: mName(name), mFilename(filename), mLine(line)
{
	xTestRegistry::Instance().Add(this);
}

xTest::~xTest()
{
}

const xString& xTest::Name() const
{
	return mName;
}

void xTest::Run(xTestListener* listener)
{
	listener->StartTest(this);
	RunTest(listener);
	listener->EndTest();
}