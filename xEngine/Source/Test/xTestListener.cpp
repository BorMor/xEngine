#include "xEngine.h"
#include "Test/xTest.h"
#include "Test/xTestListener.h"

xTestListener::xTestListener()
{
}

xTestListener::~xTestListener()
{
}

void xTestListener::AddFailure(const xString& condition, const xString& test_name, const xString& filename, int line)
{
}

void xTestListener::StartTest(xTest* test)
{
}

void xTestListener::EndTest()
{
}