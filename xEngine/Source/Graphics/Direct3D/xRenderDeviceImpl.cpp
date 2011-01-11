#include "xEngine.h"
#include "xPrerequisites.h"
#include "xProgramImpl.h"
#include "xRenderWindowImpl.h"
#include "xIndexBufferImpl.h"
#include "xVertexBufferImpl.h"
#include "xVertexFormatImpl.h"
#include "xPixelShaderImpl.h"
#include "xVertexShaderImpl.h"
#include "xConstantBufferImpl.h"

ID3D10Device*	gDevice = 0;

// d3d10 mapping for xVertexElementUsage
static char* semantic_names[] =
{
	"POSITION",	// xVertexElementUsage::Position
	"NORMAL",	// xVertexElementUsage::Normal
	"COLOR",	// xVertexElementUsage::Diffuse
	"TEXCOORD",	// xVertexElementUsage::TexCoord
};

// d3d10 mapping for xVertexElementType
static DXGI_FORMAT element_formats[] = 
{
	DXGI_FORMAT_R32_FLOAT,			// xVertexElementType::Float,
	DXGI_FORMAT_R32G32_FLOAT,		// xVertexElementType::Vector2,
	DXGI_FORMAT_R32G32B32_FLOAT,	// xVertexElementType::Vector3,
	DXGI_FORMAT_R32G32B32A32_FLOAT,	// xVertexElementType::Vector4,
	DXGI_FORMAT_R8G8B8A8_UNORM,		// xVertexElementType::Color
};

struct xRenderDevice::Impl
{
	xProgram::Impl*			mProgramImpl;
	bool					mInputLayoutChanged;
	xVertexBuffer::Impl*	mVertexBufferImpl;

	void SetupInputLayout()
	{
		if (mInputLayoutChanged)
		{
			if (mVertexBufferImpl)
			{
				xVertexFormat* vertex_format = mVertexBufferImpl->mVertexFormat;
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

					ID3D10Blob* blob = mProgramImpl->mVertexShader->pImpl->mCompiledShader;
					HRESULT hr = gDevice->CreateInputLayout(descs, n_elements, blob->GetBufferPointer(), blob->GetBufferSize(), &vertex_format->pImpl->mLayout);
					delete[] descs;
				}
		
				gDevice->IASetInputLayout(vertex_format->pImpl->mLayout);
			}
			else
				gDevice->IASetInputLayout(NULL);
		}
	}
};	

xRenderDevice::xRenderDevice(xRenderWindow* window)
{
	pImpl = new Impl();
	
	HWND hWnd = (HWND)window->Handle();
	RECT rc;
    GetClientRect(hWnd, &rc);
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;
UINT flags = 0;
#ifdef xDEBUG
	flags = D3D10_CREATE_DEVICE_DEBUG;
#endif
	D3D10CreateDevice(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, flags, D3D10_SDK_VERSION, &gDevice);		
	
	D3D10_RASTERIZER_DESC desc;
	desc.FillMode = D3D10_FILL_SOLID;
    desc.CullMode = D3D10_CULL_BACK;
    desc.FrontCounterClockwise = false;
    desc.DepthBias = false;
    desc.DepthBiasClamp = 0;
    desc.SlopeScaledDepthBias = 0;
    desc.DepthClipEnable = false;
    desc.ScissorEnable = false;
    desc.MultisampleEnable = false;
    desc.AntialiasedLineEnable = false;
	
	ID3D10RasterizerState* state = NULL;
	gDevice->CreateRasterizerState(&desc, &state);
	gDevice->RSSetState(state);
	window->pImpl->Init();	

	pImpl->mProgramImpl = NULL;
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

#define PREPARE_BUFFERS(BUFFERS)																			\
{																											\
	n = BUFFERS.Size();																						\
	if (n > 0)																								\
	{																										\
		buffers = new ID3D10Buffer*[n];																		\
		size_t i = 0;																						\
		for (xProgram::Impl::BufferList::Iterator it = BUFFERS.Begin(); it != BUFFERS.End(); ++it, ++i)		\
		{																									\
			xConstantBuffer* buffer = (*it);																\
			buffer->Flush();																				\
			buffers[i] = buffer->pImpl->mBuffer;															\
		}																									\
	}																										\
}


void xRenderDevice::SetProgram(xProgram* program)
{
	pImpl->mProgramImpl = program ? program->pImpl : NULL;
	if (pImpl->mProgramImpl)
	{

		size_t n = 0;
		ID3D10Buffer** buffers = 0;

		PREPARE_BUFFERS(pImpl->mProgramImpl->mVSBuffers);
		if (n > 0)
		{
			gDevice->VSSetConstantBuffers(0, n, buffers);
			xSAFE_ARRAY_DELETE(buffers);
		}

		gDevice->VSSetShader(pImpl->mProgramImpl->mVertexShader->pImpl->mShader);
		
		PREPARE_BUFFERS(pImpl->mProgramImpl->mPSBuffers);
		if (n > 0)
		{
			gDevice->PSSetConstantBuffers(0, n, buffers);
			xSAFE_ARRAY_DELETE(buffers);
		}
				
		gDevice->PSSetShader(pImpl->mProgramImpl->mPixelShader->pImpl->mShader);

		//@todo: gs
	}
}


void xRenderDevice::SetIndexBuffer(xIndexBuffer* buffer)
{
	DXGI_FORMAT format = buffer->Format() == xIndexFormat::UInt16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
	gDevice->IASetIndexBuffer(buffer->pImpl->mBuffer, format, 0);
}

void xRenderDevice::SetVertexBuffer(xVertexBuffer* buffer)
{	
	if (buffer)
	{
		if (pImpl->mVertexBufferImpl != buffer->pImpl)
		{
			pImpl->mInputLayoutChanged = true;
			pImpl->mVertexBufferImpl = buffer->pImpl;
			UINT offset = 0;
			gDevice->IASetVertexBuffers( 0, 1, &buffer->pImpl->mBuffer, &buffer->mStride, &offset);
		}
	}
	else
	{
		pImpl->mInputLayoutChanged = true;
		pImpl->mVertexBufferImpl = NULL;
	}
}

void SetPrimitiveTopology(xPrimitiveType::Enum type)
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
	default:
		gDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
	}
}

void xRenderDevice::DrawPrimitive(xPrimitiveType::Enum type, xUInt32 start_vertex, xUInt32 vertex_count)
{
	pImpl->SetupInputLayout();
	SetPrimitiveTopology(type);
	gDevice->Draw(vertex_count, start_vertex);
}
void xRenderDevice::DrawIndexedPrimitive(xPrimitiveType::Enum type, xUInt32 base_vertex, xUInt32 start_index, xUInt32 index_count)
{
	pImpl->SetupInputLayout();
	SetPrimitiveTopology(type);	
	gDevice->DrawIndexed(index_count, start_index, base_vertex);
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