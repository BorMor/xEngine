#include <xEngine.h>

#if defined(xCOMPILER_MSVC)
	#include <crtdbg.h>
#endif

struct SubMesh
{
	xUInt32					StartIndex;
	xUInt32					IndexCount;
	xSharedPtr<xTexture>	DiffuseMap;
};

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
		xUInt32 id = reader.ReadUInt32();	// 'SUBM'
		size_t nsubmeshes = reader.ReadUInt32();
		for (size_t i = 0; i < nsubmeshes; i++)
		{
			SubMesh submesh;
			submesh.StartIndex = reader.ReadUInt32();
			submesh.IndexCount = reader.ReadUInt32();
			xByte len = reader.ReadByte();
			xString texture_name;
			texture_name.Reserve(len+1);			
			reader.Read(texture_name.Data(), len);
			texture_name[len] = 0;
			submesh.DiffuseMap = xTexture::LoadFromFile("Data/Textures/" + texture_name);
			mSubMeshes.AddBack(submesh);
		}
		delete stream;

		//xFile::Open("sdf");
#ifdef xRENDERSYSTEM_OPENGL
		mProgram = new xProgram("Data/Shaders/basic.vert", "Data/Shaders/basic.frag");
#else
		mProgram = new xProgram("Data/Shaders/basicVS.hlsl", "Data/Shaders/basicPS.hlsl");
#endif
//		mTexture = // new xTexture2D(256, 256, 0, xTextureFormat::DXT3);
		
		xVector3 lightDir(0.5f, -0.2f, 0.5f);
		lightDir.Normalize();

		mProgram->GetVariableByName("lightDir")->AsVector()->Set(lightDir);

		xMatrix projection, world, view;
		
		world = xMatrix::IDENTITY;
		xBuildViewMatrix(view, xVector3(-0.7f, 1.6f, -1.1f), xVector3(0.f, 1.f, 0.f), xVector3(0.f, 1.f, 0.f));				
		xBuildProjectionMatrix(projection, 90.f, 800.f / 600.f, 0.1f, 100.f);

		xMatrix worldView = world * view;
		xMatrix worldViewProj = worldView * projection;

		mProgram->GetVariableByName("worldView")->AsMatrix()->Set(worldView);
		mProgram->GetVariableByName("worldViewProj")->AsMatrix()->Set(worldViewProj);		
		return true;
	}

	void OnUpdate(float dt)
	{
		mRenderDevice->Clear(xColor::BLACK);		
		mRenderDevice->SetProgram(mProgram);
		mRenderDevice->SetIndexBuffer(mIndexBuffer);
		mRenderDevice->SetVertexBuffer(mVertexBuffer);
	
		for (xList<SubMesh>::Iterator it = mSubMeshes.Begin(); it != mSubMeshes.End(); ++it)
		{
			mProgram->GetVariableByName("diffuseMap")->AsTexture()->Set(it->DiffuseMap);
			mRenderDevice->DrawIndexedPrimitive(xPrimitiveType::TriangleList, 0, it->StartIndex, it->IndexCount);
		}

		mRenderWindow->Present();
	}

	void OnShutdown()
	{
		mSubMeshes.Clear();
		xSAFE_DELETE(mProgram);
		xSAFE_DELETE(mIndexBuffer);
		xSAFE_DELETE(mVertexBuffer);
	}
protected:
	xProgram*		mProgram;
	xVertexBuffer*	mVertexBuffer;
	xIndexBuffer*	mIndexBuffer;
	xList<SubMesh>	mSubMeshes;
};

xIMPLEMENT_APPLICATION(Application);
