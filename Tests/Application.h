#pragma once

#include "Prerequisites.h"

class Application : public xConsoleApplication, public xTestListener
{
public:
	bool OnInit();
	void Run();
	void OnShutdown();	

	void StartTest(xTest* test);
	void EndTest();
	void AddFailure(const xString& condition, const xString& test_name, const xString& filename, int line);
protected:
	int mFailedTestCount;
	bool mLastTestSuccessful;
};