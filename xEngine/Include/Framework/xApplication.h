#pragma once

class xEXPORT xApplication
{
public:
    xApplication();
    virtual ~xApplication();

	virtual bool Initialize() = 0;
	virtual void Run() = 0;
	virtual void Shutdown() = 0;

	virtual bool OnInit() = 0;
	virtual void OnShutdown() = 0;
};

#if defined(xPLATFORM_WIN32)
/***************************************************************************/
#define xIMPLEMENT_APPLICATION(T)                                           \
																			\
    INT WINAPI WinMain( HINSTANCE hInstance,                                \
                        HINSTANCE hPrevInstance,                            \
                        LPSTR lpCmdLine,                                    \
                        INT nCmdShow)                                       \
	{                                                                       \
		xApplication* XApplication = new T();                               \
		if (XApplication->Initialize())										\
			XApplication->Run();	                                        \
		XApplication->Shutdown();											\
		delete XApplication;                                                \
		return 0;                                                           \
	}
/***************************************************************************/
#elif defined(xPLATFORM_LINUX)
/***************************************************************************/
#define xIMPLEMENT_APPLICATION(T)                                           \
	int main(int argc, char **argv)                                         \
	{                                                                       \
		xApplication* XApplication = new T();                               \
		if (XApplication->Initialize())										\
			XApplication->Run();											\
		XApplication->Shutdown();											\
		delete XApplication;                                                \
		return 0;                                                           \
	}
/***************************************************************************/
#endif
