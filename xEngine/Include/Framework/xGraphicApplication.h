#pragma once

class xEXPORT xGraphicApplication : public xApplication//, public xRenderWindowClient
{
public:
	xGraphicApplication();
	~xGraphicApplication();

	bool Initialize();
	void Run();
	void Shutdown();

	virtual void OnUpdate(float dt) = 0;
protected:
	xRenderWindow*	mRenderWindow;
	xRenderDevice*	mRenderDevice;
	xTimer*			mTimer;
};
