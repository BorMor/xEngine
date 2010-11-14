#pragma once

#include "Prerequisites.h"

class Application : public xConsoleApplication, public xTestListener
{
public:
	bool OnInit();
	void OnShutdown();

	void StartTest(xTest* test);
	void EndTest();
	void AddFailure(const xString& condition, const xString& test_name, const xString& filename, int line);
	/*void StartTests();
	void EndTests();*/
protected:
	int mFailedTestCount;
	bool mLastTestSuccessful;
};