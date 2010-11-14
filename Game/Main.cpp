#include <xEngine.h>

const char vertex_shader[] = "	#version 330								\n\
								layout(location = 0) in vec4 position;		\n\
								layout(location = 2) in vec4 diffuse;		\n\
								out vec4 color;								\n\
																			\n\
								void main(void)								\n\
								{											\n\
									gl_Position = position;					\n\
									color = diffuse;						\n\
								}											\n\
							";

const char fragment_shader[] = "	#version 330								\n\
									in vec4 color;								\n\
									out vec4 fragColor;							\n\
																				\n\
									void main(void)								\n\
									{											\n\
										fragColor = color;						\n\
									}											\n\
								";

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
		mMaterial->SetVertexShader(vertex_shader);
		mMaterial->SetFragmentShader(fragment_shader);
		return true;
	}

	void OnUpdate(float dt)
	{
		mRenderDevice->Clear(xColor::BLACK);		
		mRenderDevice->SetVertexBuffer(mVertexBuffer);
		mRenderDevice->SetMaterial(mMaterial);
		mRenderDevice->DrawPrimitive(xPrimitiveType::TriangleList, 0, 3);
		//xSleep(10);
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