#include "Application.h"

xIMPLEMENT_CONSOLE_APPLICATION(Application);

bool Application::OnInit()
{
	mConsole->SetTitle("xEngine Tests");	
	return true;
}

void Application::Run()
{
	
	xTestRegistry::Instance().Run(this);
	mConsole->Print("\nPress Enter to continue...");
	mConsole->Read();
}

void Application::OnShutdown()
{
}

void Application::StartTest(xTest* test)
{
	mConsole->Print(xString(test->Name()) + "..", xConsoleColor::Yellow);
	mLastTestSuccessful = true;
}

void Application::EndTest()
{
	if (mLastTestSuccessful)
		mConsole->Print("OK",  xConsoleColor::Green);
	else
		mFailedTestCount++;
	mConsole->Print("\n");
}

void Application::AddFailure(const xString& condition, const xString& test_name, const xString& filename, int line)
{
	mConsole->Print("\nCondition: ");
	mConsole->Print(condition + "\n",  xConsoleColor::Red);
	mConsole->Print(xString::Format("File:      %s(%d)\n", filename.c_str(), line));
	mLastTestSuccessful = false;
}