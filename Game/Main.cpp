#include <xEngine.h>

class Application : public xGraphicApplication
{
	struct Vertex
	{
		xVector3	Position;
		xColor		Color;
	};
public:
	bool OnInit()
	{
		mVertexFormat = new xVertexFormat;
		mVertexFormat->AddElement(xVertexElementType::Vector3, xVertexElementUsage::Position);
		mVertexFormat->AddElement(xVertexElementType::Color, xVertexElementUsage::Diffuse);

		mVertexBuffer = new xVertexBuffer(mVertexFormat, 3, sizeof(Vertex));
		Vertex* vertices = (Vertex*)mVertexBuffer->Lock();
		vertices[0].Position = xVector3(-0.5f, -0.5f, 0.f);
		vertices[0].Color = xColor::RED;
		vertices[1].Position = xVector3(0.5f, -0.5f, 0.f);
		vertices[1].Color = xColor::GREEN;
		vertices[2].Position = xVector3(0.f, 0.5f, 0.f);
		vertices[2].Color = xColor::BLUE;
		mVertexBuffer->Unlock();

		mMaterial = new xMaterial();
		mMaterial->SetVertexShader("Data/Shaders/basic.vert");
		mMaterial->SetFragmentShader("Data/Shaders/basic.frag");
		return true;
	}

	void OnUpdate(float dt)
	{
		mRenderDevice->Clear(xColor::BLACK);		
		mRenderDevice->SetVertexBuffer(mVertexBuffer);
		mRenderDevice->SetMaterial(mMaterial);
		mRenderDevice->DrawPrimitive(xPrimitiveType::TriangleList, 0, 3);
		mRenderDevice->Present();
	}
	
	void OnShutdown()
	{
		xSAFE_DELETE(mMaterial);
		xSAFE_DELETE(mVertexBuffer);
		xSAFE_DELETE(mVertexFormat);
	}
protected:
	xMaterial*		mMaterial;
	xVertexFormat*	mVertexFormat;
	xVertexBuffer*	mVertexBuffer;
};

xIMPLEMENT_APPLICATION(Application);