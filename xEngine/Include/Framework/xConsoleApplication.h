#pragma once

class xEXPORT xConsoleApplication : public xApplication
{
public:
	xConsoleApplication();
	~xConsoleApplication();

	bool Initialize();
	void Shutdown();
protected:
	xConsole* mConsole;
};
