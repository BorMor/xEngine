#include "xEngine.h"

xApplication*   XApplication = NULL;

xApplication::xApplication()
{
	mLogFileWriter = new xLogFileWriter("log.txt");
	xLog.AddListener(mLogFileWriter);
}

xApplication::~xApplication()
{
	xLog.RemoveListener(mLogFileWriter);
	xSAFE_DELETE(mLogFileWriter);
}
