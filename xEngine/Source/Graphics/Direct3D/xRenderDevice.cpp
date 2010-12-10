#include "xEngine.h"
#include "xPrerequisites.h"
#include "xGPUProgramImpl.h"
#include "xRenderWindowImpl.h"
#include "xVertexBufferImpl.h"
#include "xVertexFormatImpl.h"
#include "xPixelShaderImpl.h"
#include "xVertexShaderImpl.h"

ID3D10Device*	gDevice = 0;

struct xRenderDevice::Impl
{
	xGPUProgram*	mProgram;
};	

xRenderDevice::xRenderDevice(xRenderWindow* window)
{
	pImpl = new Impl();
	
	HWND hWnd = (HWND)window->Handle();
	RECT rc;
    GetClientRect(hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

	D3D10CreateDevice(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, &gDevice);		
	window->pImpl->Init();	

	pImpl->mProgram = NULL;
}

xRenderDevice::~xRenderDevice()
{
	if (gDevice)
		gDevice->ClearState();
    
	if (gDevice)
		gDevice->Release();

	xSAFE_DELETE(pImpl);
}

void xRenderDevice::Clear(const xColor& color)
{
	float fcolor[4];
	fcolor[0] = color.R / 255.f;
	fcolor[1] = color.G / 255.f;
	fcolor[2] = color.B / 255.f;
	fcolor[3] = color.A / 255.f;
	ID3D10RenderTargetView* target = NULL;
	gDevice->OMGetRenderTargets(1, &target, NULL);
	gDevice->ClearRenderTargetView(target, fcolor);
}


// d3d10 mapping for xVertexElementUsage
static char* semantic_names[] =
{
	"POSITION",	// xVertexElementUsage::Position
	"NORMAL",	// xVertexElementUsage::Normal
	"COLOR",	// xVertexElementUsage::Diffuse
	"TEXCOORD",	// xVertexElementUsage::TexCoord
};

void xRenderDevice::SetProgram(xGPUProgram* program)
{
	pImpl->mProgram = program;
	if (pImpl->mProgram)
	{
		gDevice->VSSetShader(pImpl->mProgram->pImpl->mVertexShader->pImpl->mShader);
		gDevice->PSSetShader(pImpl->mProgram->pImpl->mPixelShader->pImpl->mShader);
	}
}

// d3d10 mapping for xVertexElementType
static DXGI_FORMAT element_formats[] = 
{
	DXGI_FORMAT_R32_FLOAT,			// xVertexElementType::Float,
	DXGI_FORMAT_R32G32_FLOAT,		// xVertexElementType::Vector2,
	DXGI_FORMAT_R32G32B32_FLOAT,	// xVertexElementType::Vector3,
	DXGI_FORMAT_R32G32B32A32_FLOAT,	// xVertexElementType::Vector4,
	DXGI_FORMAT_R8G8B8A8_UNORM,		// xVertexElementType::Color
};

void xRenderDevice::SetVertexBuffer(xVertexBuffer* buffer)
{
	if (buffer)
	{
		xVertexFormat* vertex_format = buffer->pImpl->mVertexFormat;
		if (!vertex_format->pImpl->mLayout)
		{		
			UINT n_elements = vertex_format->mElements.Size();
			D3D10_INPUT_ELEMENT_DESC* descs = new D3D10_INPUT_ELEMENT_DESC[n_elements];
			for (size_t i = 0; i < n_elements; i++)
			{
				const xVertexFormat::Element& el = vertex_format->mElements[i];
				descs[i].SemanticName = semantic_names[el.Usage]; 
				descs[i].SemanticIndex = 0;
				descs[i].Format = element_formats[el.Type];
				descs[i].InputSlot = 0;
				descs[i].AlignedByteOffset = el.Offset;
				descs[i].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
				descs[i].InstanceDataStepRate = 0;
			};

			ID3D10Blob* blob = pImpl->mProgram->pImpl->mVertexShader->pImpl->mCompiledShader;
			HRESULT hr = gDevice->CreateInputLayout(descs, n_elements, blob->GetBufferPointer(), blob->GetBufferSize(), &vertex_format->pImpl->mLayout);
			delete[] descs;
		}
		
		gDevice->IASetInputLayout(vertex_format->pImpl->mLayout);

		UINT offset = 0;
		gDevice->IASetVertexBuffers( 0, 1, &buffer->pImpl->mBuffer, &buffer->mStride, &offset);
	}
}

void xRenderDevice::DrawPrimitive(xPrimitiveType::Enum type, xUInt32 start_vertex, xUInt32 vertex_count)
{
	
	switch (type)
	{
	case xPrimitiveType::PointList:
		gDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case xPrimitiveType::LineList:
		gDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case xPrimitiveType::LineStrip:
		gDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
		break;					
	case xPrimitiveType::TriangleList:
		gDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case xPrimitiveType::TriangleStrip:
		gDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	}
	gDevice->Draw(vertex_count, start_vertex);
}

void xRenderDevice::Present()
{
//	pImpl->mSwapChain->Present(0, 0);
	//pImpl->mContext->SwapBuffers();
}

void xRenderDevice::SetUniform(const xString& name, const xMatrix& value)
{
	/*if (pImpl->mMaterial)
	{
		ID3D10ShaderReflection* reflection = pImpl->mMaterial->pImpl->mVertexShader->pImpl->mReflection;
		ID3D10ShaderReflectionConstantBuffer* buffer = reflection->GetConstantBufferByName("$Global");
		if (buffer)
		{
			ID3D10ShaderReflectionVariable* var = buffer->GetVariableByName(name.c_str());
			ID3D10ShaderReflectionType* type = var->GetType();
			D3D10_SHADER_VARIABLE_DESC desc;
			HRESULT hr = var->GetDesc(&desc);
			int a = 1;
		}
	}*/

	/*					hr = mShaderReflectionConstantBuffer->GetDesc(&mConstantBufferDesc);

					createConstantBuffer(mConstantBufferDesc.Size);

					for(unsigned int i = 0; i < mConstantBufferDesc.Variables ; i++)
					{

						ID3D10ShaderReflectionVariable* varRef;
						varRef = mShaderReflectionConstantBuffer->GetVariableByIndex(i);

						D3D10_SHADER_VARIABLE_DESC shaderVerDesc;
						HRESULT hr = varRef->GetDesc(&shaderVerDesc);

						ShaderVarWithPosInBuf newVar;
						newVar.var = shaderVerDesc;
						newVar.wasInit = false;


						mShaderVars.push_back(newVar);
					}*/

	//pImpl->mMaterial->pImpl->mVertexShader->pImpl->mShader->
	/*if (pImpl->mMaterial)
	{
		GLint location = glGetUniformLocation(pImpl->mMaterial->pImpl->mProgram, name.c_str());
		if (location != -1)
			glUniformMatrix4fv(location, 1, GL_FALSE, &value.M00);
	}*/
}