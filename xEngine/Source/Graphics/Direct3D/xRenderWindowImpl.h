#pragma once

#include "xPrerequisites.h"

struct xRenderWindow::Impl
{
	WNDCLASSEX  mWindowClass;
	HWND        mHandle;
	bool		mClosed;

	IDXGISwapChain*			mSwapChain;
	ID3D10RenderTargetView*	mRenderTargetView;

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
	
		// Create a render target view
		ID3D10Texture2D* pBackBuffer;
		mSwapChain->GetBuffer(0, __uuidof( ID3D10Texture2D ), (LPVOID*)&pBackBuffer);

		gDevice->CreateRenderTargetView(pBackBuffer, NULL, &mRenderTargetView);
		pBackBuffer->Release();
    
		gDevice->OMSetRenderTargets(1, &mRenderTargetView, NULL);

		// Setup the viewport
		D3D10_VIEWPORT vp;
		vp.Width = width;
		vp.Height = height;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		gDevice->RSSetViewports(1, &vp);
	}
};