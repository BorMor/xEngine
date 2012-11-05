#pragma once

#include "xPrerequisites.h"

struct xRenderWindow::Impl
{
	WNDCLASSEX  mWindowClass;
	HWND        mHandle;
	bool		mClosed;

	IDXGISwapChain*			mSwapChain;
	ID3D11RenderTargetView*	mRenderTargetView;
	ID3D11DepthStencilView*	mDepthStencilView;

	void Init()
	{
		RECT rc;
		GetClientRect(mHandle, &rc);
		UINT width = rc.right - rc.left;
		UINT height = rc.bottom - rc.top;

		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory( &sd, sizeof( sd ) );
		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = mHandle;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
	
		IDXGIDevice* device = NULL;
		gDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&device));

		IDXGIAdapter* adapter = NULL;
		device->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&adapter));

		IDXGIFactory* factory = NULL;
		adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory));
		factory->CreateSwapChain(device, &sd, &mSwapChain);
		device->Release();
		adapter->Release();
		factory->Release();
	
		// Create a render target view
		ID3D11Texture2D* pBackBuffer;
		mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		gDevice->CreateRenderTargetView(pBackBuffer, NULL, &mRenderTargetView);
		pBackBuffer->Release();

		ID3D11Texture2D* pDepthStencilBuffer;

		D3D11_TEXTURE2D_DESC depth_desc;
		ZeroMemory(&depth_desc, sizeof(D3D11_TEXTURE2D_DESC));
		depth_desc.Width = width;
		depth_desc.Height = height;
		depth_desc.MipLevels = 1;
		depth_desc.ArraySize = 1;
		depth_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depth_desc.SampleDesc.Count = 1;
		depth_desc.SampleDesc.Quality = 0;
		depth_desc.Usage = D3D11_USAGE_DEFAULT;
		depth_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depth_desc.CPUAccessFlags = 0;
		depth_desc.MiscFlags = 0;
		gDevice->CreateTexture2D(&depth_desc, NULL, &pDepthStencilBuffer);

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC view_desc;
		ZeroMemory( &view_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC) );
		view_desc.Format = depth_desc.Format;
		view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		view_desc.Texture2D.MipSlice = 0;
		gDevice->CreateDepthStencilView(pDepthStencilBuffer, &view_desc, &mDepthStencilView);
		pDepthStencilBuffer->Release();
    
		gDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

		// Setup the viewport
		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)width;
		vp.Height = (FLOAT)height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		gDeviceContext->RSSetViewports(1, &vp);
	}
};