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
		
		mMaterial = new xMaterial();
		///*
		//OpenGL
		mMaterial->SetVertexShader("Data/Shaders/basic.vert");//vertex_shader);
		mMaterial->SetFragmentShader("Data/Shaders/basic.frag");//pixel_shader);//*/
		/*
		//Direct3D
		mMaterial->SetVertexShader("Data/Shaders/basicVS.hlsl");//vertex_shader);
		mMaterial->SetFragmentShader("Data/Shaders/basicPS.hlsl");//*/
		return true;
	}

	void OnUpdate(float dt)
	{
		mRenderDevice->Clear(xColor::BLACK);		
		mRenderDevice->SetMaterial(mMaterial);
		mRenderDevice->SetVertexBuffer(mVertexBuffer);
		mRenderDevice->DrawPrimitive(xPrimitiveType::PointList, 0, mVertexBuffer->VertexCount());
		mRenderWindow->Present();
	}
	
	void OnShutdown()
	{
		xSAFE_DELETE(mMaterial);
		xSAFE_DELETE(mVertexBuffer);
	}
protected:
	xMaterial*		mMaterial;
	xVertexBuffer*	mVertexBuffer;
};

xIMPLEMENT_APPLICATION(Application);