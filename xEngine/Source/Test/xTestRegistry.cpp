#include "xEngine.h"
#include "Test/xTest.h"
#include "Test/xTestRegistry.h"

xTestRegistry::xTestRegistry()
{
}

xTestRegistry& xTestRegistry::Instance()
{
	static xTestRegistry instance;
	return instance;
}
    
void xTestRegistry::Add(xTest* test)
{
	Instance().mTests.AddBack(test);
}

void xTestRegistry::Run(xTestListener* listener)
{
	for (TestList::Iterator it = mTests.Begin(); it != mTests.End(); ++it)
		(*it)->Run(listener);
}