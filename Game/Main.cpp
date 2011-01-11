#include <xEngine.h>

#if defined(xCOMPILER_MSVC)
	#include <crtdbg.h>
#endif

class Application : public xGraphicApplication
{
public:
	bool OnInit()
	{
#if defined(xCOMPILER_MSVC)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(166); // for memory leak
#endif

		/*xVertexFormat* vertex_format = new xVertexFormat();
		vertex_format->AddElement(xVertexElementType::Vector3, xVertexElementUsage::Position);
		mVertexBuffer = new xVertexBuffer(vertex_format, 3, vertex_format->VertexSize());
		xVector3* vertices = (xVector3*)mVertexBuffer->Lock();
		vertices[0] = xVector3(0.f, 0.f, 0.f);
		vertices[1] = xVector3(0.f, 0.5f, 0.f);
		vertices[2] = xVector3(1.f, 0.f, 0.f);
		mVertexBuffer->Unlock();
		*/
		xFileStream* stream = new xFileStream("Data/Meshes/nanosuit.mesh", xAccessMode::Read);
		xBinaryReader reader(stream);
		reader.ReadUInt32();	// 'MESH'
		
		mVertexBuffer = xVertexBuffer::LoadFromStream(stream);
		mIndexBuffer = xIndexBuffer::LoadFromStream(stream);
		delete stream;

		//xFile::Open("sdf");
#ifdef xRENDERSYSTEM_OPENGL
		mProgram = new xProgram("Data/Shaders/basic.vert", "Data/Shaders/basic.frag");
#else
		mProgram = new xProgram("Data/Shaders/basicVS.hlsl", "Data/Shaders/basicPS.hlsl");
#endif
		mTexture = xTexture2D::LoadFromFile("Data/Textures/NanoSuitBody_diffuse.dds");// new xTexture2D(256, 256, 0, xTextureFormat::DXT3);
		bool f1 = mProgram->GetVariableByName("diffuse")->IsValid();
		xProgramVectorVariable* diffuse = mProgram->GetVariableByName("diffuse")->AsVector();
		bool f2= diffuse->IsValid();
		//diffuse->
		xVector4 value(1.f, 0.f, 0.f, 1.f);
		diffuse->Set(value);

		xMatrix projection, world, view;
		
		world = xMatrix::IDENTITY;
		xBuildViewMatrix(view, xVector3(1.f, 2.f, 2.f), xVector3(0.f, 1.f, 0.f), xVector3(0.f, 1.f, 0.f));				
		xBuildProjectionMatrix(projection, 90.f, 800.f / 600.f, 0.1f, 100.f);

		xMatrix worldViewProj = world * view * projection;

		mProgram->GetVariableByName("worldViewProj")->AsMatrix()->Set(worldViewProj);
		mProgram->GetVariableByName("world")->AsMatrix()->Set(world);
		mProgram->GetVariableByName("view")->AsMatrix()->Set(view);
		mProgram->GetVariableByName("proj")->AsMatrix()->Set(projection);

		return true;
	}

	void OnUpdate(float dt)
	{
		mRenderDevice->Clear(xColor::BLACK);
		mRenderDevice->SetProgram(mProgram);
		mRenderDevice->SetIndexBuffer(mIndexBuffer);
		mRenderDevice->SetVertexBuffer(mVertexBuffer);
		mRenderDevice->DrawIndexedPrimitive(xPrimitiveType::TriangleList, 0, 0, mIndexBuffer->IndexCount());
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
	xProgram*		mProgram;
	xVertexBuffer*	mVertexBuffer;
	xIndexBuffer*	mIndexBuffer;
	xTexture2D*		mTexture;
};

xIMPLEMENT_APPLICATION(Application);
