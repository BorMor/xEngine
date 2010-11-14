#include "Application.h"

xIMPLEMENT_APPLICATION(Application);

bool Application::OnInit()
{
	mConsole->SetTitle("xEngine Tests");
	xTestRegistry::Instance().Run(this);
	return true;
}

void Application::OnShutdown()
{	
}

void Application::StartTest(xTest* test)
{
	mConsole->Print(xString(test->Name()) + "..", xColor::YELLOW);
	mLastTestSuccessful = true;
}

void Application::EndTest()
{
	if (mLastTestSuccessful)
		mConsole->Print("OK", xColor::GREEN);
	else
		mFailedTestCount++;
	mConsole->Print("\n");
}

void Application::AddFailure(const xString& condition, const xString& test_name, const xString& filename, int line)
{
	mConsole->Print("\nCondition: ");
	mConsole->Print(condition + "\n", xColor::RED);
	mConsole->Print(xString::Format("File:      %s(%d)\n", filename.c_str(), line));
	mLastTestSuccessful = false;
}
/*
void Application::StartTests()
{
	TestResult::StartTests();
	mFailedTestCount = 0;
}

void Application::EndTests()
{
	TestResult::EndTests();

	static char buf[256];
	if (m_failureCount != 0)
	{
		sprintf_s(buf, 256, "\nFailed %d of %d tests\n", mFailedTestCount, mTestCount);
		mConsole->Print(buf, xColor::RED);
	}
	else
		mConsole->Print("\nAll tests successful\n", xColor::GREEN);
}*/