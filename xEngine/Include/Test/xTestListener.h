#pragma once

class xTest;

class xEXPORT xTestListener
{
public:
	xTestListener();
	virtual ~xTestListener();

	virtual void AddFailure(const xString& condition, const xString& test_name, const xString& filename, int line);
	virtual void StartTest(xTest* test);
	virtual void EndTest();
};
