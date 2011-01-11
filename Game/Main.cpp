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
		mIndexBuffer = xIndexBuffer::LoadFromStream(stream);
		delete stream;
		
		//xFile::Open("sdf");
#ifdef xRENDERSYSTEM_DIRECT3D
		mProgram = new xGPUProgram("Data/Shaders/basicVS.hlsl", "Data/Shaders/basicPS.hlsl");
#else		
		mProgram = new xGPUProgram("Data/Shaders/basic.vert", "Data/Shaders/basic.frag");
#endif
		mTexture = xTexture2D::LoadFromFile("Data/Textures/NanoSuitBody_diffuse.dds");// new xTexture2D(256, 256, 0, xTextureFormat::DXT3);
		return true;
	}

	void OnUpdate(float dt)
	{
		mRenderDevice->Clear(xColor::BLACK);		
		mRenderDevice->SetProgram(mProgram);
		mRenderDevice->SetIndexBuffer(mIndexBuffer);
		mRenderDevice->SetVertexBuffer(mVertexBuffer);
		mRenderDevice->DrawIndexedPrimitive(xPrimitiveType::TriangleList, 0, 0, mIndexBuffer->IndexCount());
		//mRenderDevice->DrawPrimitive(xPrimitiveType::PointList, 0, mVertexBuffer->VertexCount());
		mRenderWindow->Present();
	}
	
	void OnShutdown()
	{
		xSAFE_DELETE(mTexture);
		xSAFE_DELETE(mProgram);
		xSAFE_DELETE(mIndexBuffer);
		xSAFE_DELETE(mVertexBuffer);
	}
protected:
	xGPUProgram*	mProgram;
	xVertexBuffer*	mVertexBuffer;
	xIndexBuffer*	mIndexBuffer;
	xTexture2D*		mTexture;
};

xIMPLEMENT_APPLICATION(Application);