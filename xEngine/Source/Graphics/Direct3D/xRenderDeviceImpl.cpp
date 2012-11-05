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
#include "xTextureImpl.h"

ID3D11Device*			gDevice = NULL;
ID3D11DeviceContext*	gDeviceContext = NULL;

// d3d11 mapping for xVertexElementUsage
static char* semantic_names[] =
{
	"POSITION",	// xVertexElementUsage::Position
	"NORMAL",	// xVertexElementUsage::Normal
	"COLOR",	// xVertexElementUsage::Diffuse
	"TEXCOORD",	// xVertexElementUsage::TexCoord
};

// d3d11 mapping for xVertexElementType
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

	void BindNecessaryData()
	{
		if (mProgramImpl)
		{
			ID3D11ShaderResourceView* no_view = NULL;
			for (UINT i = 0; i < 128; i++)
			{
				gDeviceContext->VSSetShaderResources(i, 1, &no_view);
				gDeviceContext->PSSetShaderResources(i, 1, &no_view);
			}

			for (xProgram::Impl::BufferList::Iterator it = mProgramImpl->mVSBuffers.Begin(); it != mProgramImpl->mVSBuffers.End(); ++it)
				(*it)->Flush();			

			for (xProgram::Impl::ResourceList::Iterator it = mProgramImpl->mVSResources.Begin(); it != mProgramImpl->mVSResources.End(); ++it)
			{
				xShaderResource& resource = *it;
				if (resource.mType == xShaderResource::Texture)
				{
					const xTexture* texture = resource.mTextureVariable->mTexture;
					if (texture)
						gDeviceContext->VSSetShaderResources(resource.mSlot, 1, &texture->pImpl->mShaderResourceView);
				}
			}		
		
			for (xProgram::Impl::BufferList::Iterator it = mProgramImpl->mPSBuffers.Begin(); it != mProgramImpl->mPSBuffers.End(); ++it)
				(*it)->Flush();

			for (xProgram::Impl::ResourceList::Iterator it = mProgramImpl->mPSResources.Begin(); it != mProgramImpl->mPSResources.End(); ++it)
			{
				xShaderResource& resource = *it;
				if (resource.mType == xShaderResource::Texture)
				{
					const xTexture* texture = resource.mTextureVariable->mTexture;
					if (texture)
						gDeviceContext->PSSetShaderResources(resource.mSlot, 1, &texture->pImpl->mShaderResourceView);
				}
			}
		}

		if (mInputLayoutChanged)
		{
			if (mVertexBufferImpl)
			{
				xVertexFormat* vertex_format = mVertexBufferImpl->mVertexFormat;
				if (!vertex_format->pImpl->mLayout)
				{		
					UINT n_elements = vertex_format->mElements.Size();
					D3D11_INPUT_ELEMENT_DESC* descs = new D3D11_INPUT_ELEMENT_DESC[n_elements];
					for (size_t i = 0; i < n_elements; i++)
					{
						const xVertexFormat::Element& el = vertex_format->mElements[i];
						descs[i].SemanticName = semantic_names[el.Usage]; 
						descs[i].SemanticIndex = 0;
						descs[i].Format = element_formats[el.Type];
						descs[i].InputSlot = 0;
						descs[i].AlignedByteOffset = el.Offset;
						descs[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
						descs[i].InstanceDataStepRate = 0;
					};

					ID3DBlob* blob = mProgramImpl->mVertexShader->pImpl->mCompiledShader;
					HRESULT hr = gDevice->CreateInputLayout(descs, n_elements, blob->GetBufferPointer(), blob->GetBufferSize(), &vertex_format->pImpl->mLayout);
					delete[] descs;
				}
		
				gDeviceContext->IASetInputLayout(vertex_format->pImpl->mLayout);
			}
			else
				gDeviceContext->IASetInputLayout(NULL);
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
	flags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0
    };
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_FEATURE_LEVEL featureLevel;

	D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &gDevice, &featureLevel, &gDeviceContext);	
	
	D3D11_RASTERIZER_DESC desc;
	desc.FillMode = D3D11_FILL_SOLID;
    desc.CullMode = D3D11_CULL_BACK;
    desc.FrontCounterClockwise = true;
    desc.DepthBias = false;
    desc.DepthBiasClamp = 0;
    desc.SlopeScaledDepthBias = 0;
    desc.DepthClipEnable = true;
    desc.ScissorEnable = false;
    desc.MultisampleEnable = false;
    desc.AntialiasedLineEnable = false;
	
	ID3D11RasterizerState* state = NULL;
	gDevice->CreateRasterizerState(&desc, &state);
	gDeviceContext->RSSetState(state);
	state->Release();
	window->pImpl->Init();

	pImpl->mProgramImpl = NULL;
}

xRenderDevice::~xRenderDevice()
{
#if defined(xDEBUG)
	/*ID3D11Debug* debug = 0; 
	gDevice->QueryInterface(IID_ID3D11Debug, (void**) &debug); 
	debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	debug->Release();*/
#endif

	if (gDeviceContext)
	{
		gDeviceContext->ClearState();
		gDeviceContext->Release();
	}
    
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
	ID3D11RenderTargetView* target = NULL;
	ID3D11DepthStencilView* depth_stencil = NULL;
	gDeviceContext->OMGetRenderTargets(1, &target, &depth_stencil);
	
	gDeviceContext->ClearRenderTargetView(target, fcolor);
	gDeviceContext->ClearDepthStencilView(depth_stencil, D3D11_CLEAR_DEPTH, 1.f, 0);
	target->Release();
	depth_stencil->Release();
}

void xRenderDevice::SetProgram(xProgram* program)
{
	pImpl->mProgramImpl = program ? program->pImpl : NULL;
	if (pImpl->mProgramImpl)
	{		
		int i = 0;
		for (xProgram::Impl::BufferList::Iterator it = pImpl->mProgramImpl->mVSBuffers.Begin(); it != pImpl->mProgramImpl->mVSBuffers.End(); ++it, ++i)
			gDeviceContext->VSSetConstantBuffers(i, 1, &(*it)->pImpl->mBuffer);
		gDeviceContext->VSSetShader(pImpl->mProgramImpl->mVertexShader->pImpl->mShader, NULL, 0);		
		
		
		i = 0;
		for (xProgram::Impl::BufferList::Iterator it = pImpl->mProgramImpl->mPSBuffers.Begin(); it != pImpl->mProgramImpl->mPSBuffers.End(); ++it, ++i)
			gDeviceContext->PSSetConstantBuffers(i, 1, &(*it)->pImpl->mBuffer);		
		gDeviceContext->PSSetShader(pImpl->mProgramImpl->mPixelShader->pImpl->mShader, NULL, 0);
		//@todo: gs
	}
}


void xRenderDevice::SetIndexBuffer(xIndexBuffer* buffer)
{
	DXGI_FORMAT format = buffer->Format() == xIndexFormat::UInt16 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
	gDeviceContext->IASetIndexBuffer(buffer->pImpl->mBuffer, format, 0);
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
			gDeviceContext->IASetVertexBuffers( 0, 1, &buffer->pImpl->mBuffer, &buffer->mStride, &offset);
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
		gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case xPrimitiveType::LineList:
		gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case xPrimitiveType::LineStrip:
		gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		break;					
	case xPrimitiveType::TriangleList:
		gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case xPrimitiveType::TriangleStrip:
		gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	default:
		gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	}
}

void xRenderDevice::DrawPrimitive(xPrimitiveType::Enum type, xUInt32 start_vertex, xUInt32 vertex_count)
{
	pImpl->BindNecessaryData();
	SetPrimitiveTopology(type);
	gDeviceContext->Draw(vertex_count, start_vertex);
}
void xRenderDevice::DrawIndexedPrimitive(xPrimitiveType::Enum type, xUInt32 base_vertex, xUInt32 start_index, xUInt32 index_count)
{
	pImpl->BindNecessaryData();
	SetPrimitiveTopology(type);	
	gDeviceContext->DrawIndexed(index_count, start_index, base_vertex);
}

void xRenderDevice::Present()
{
//	pImpl->mSwapChain->Present(0, 0);
	//pImpl->mContext->SwapBuffers();
}