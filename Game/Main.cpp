#include <xEngine.h>

class Application : public xGraphicApplication
{
public:
	bool OnInit()
	{
		xFileStream* stream = new xFileStream("Data/Meshes/nanosuit.mesh", xAccessMode::Read);
		xBinaryReader reader(stream);
		reader.ReadUInt32();	// 'MESH'		

		mVertexBuffer = xVertexBuffer::LoadFromStream(stream);
		delete stream;
		
		//xFile::Open("sdf");
#ifdef xRENDERSYSTEM_OPENGL
		mProgram = new xGPUProgram("Data/Shaders/basic.vert", "Data/Shaders/basic.frag");
#else		
		mProgram = new xGPUProgram("Data/Shaders/basicVS.hlsl", "Data/Shaders/basicPS.hlsl");
#endif
		return true;
	}

	void OnUpdate(float dt)
	{
		mRenderDevice->Clear(xColor::BLACK);		
		mRenderDevice->SetProgram(mProgram);
		mRenderDevice->SetVertexBuffer(mVertexBuffer);
		mRenderDevice->DrawPrimitive(xPrimitiveType::PointList, 0, mVertexBuffer->VertexCount());
		mRenderWindow->Present();
	}
	
	void OnShutdown()
	{
		xSAFE_DELETE(mProgram);
		xSAFE_DELETE(mVertexBuffer);
	}
protected:
	xGPUProgram*	mProgram;
	xVertexBuffer*	mVertexBuffer;
};

xIMPLEMENT_APPLICATION(Application);