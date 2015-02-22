#include "Render.h"

Render::Render(){
	_sceneColor = new float[4] { 0.0f, 0.125f, 0.3f, 1.0f };
	_device = 0;
	_immediateContext = 0;
	_swapChain = 0;
	_renderTargetView = 0;
	_backBuffer = 0;
	_depthStencil = 0;
	_depthStencilView = 0;
}
bool Render::initialize(HWND hwnd, int sizeX, int sizeY){
	_sizeX = sizeX; 
	_sizeY = sizeY;
	HRESULT hr;
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = _sizeX;
	sd.BufferDesc.Height = _sizeY;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for(UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, _driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &_swapChain, &_device, &_featureLevel, &_immediateContext);
		if(SUCCEEDED(hr))			break;
	}
	CHECK_RESULT(hr, "Creation of device & swapChain failed");
	CHECK_RESULT(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer), "Getting backbuffer of swapChain failed");
	CHECK_RESULT(_device->CreateRenderTargetView(_backBuffer, NULL, &_renderTargetView), "Creation of RenderTargetView failed");

	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = _sizeX;
	descDepth.Height = _sizeY;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	CHECK_RESULT(_device->CreateTexture2D(&descDepth, NULL, &_depthStencil), "Creation of depth stencil texture failed");

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	CHECK_RESULT(_device->CreateDepthStencilView(_depthStencil, &descDSV, &_depthStencilView), "Creation of depth stencil view failed");

	_immediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)_sizeX;
	vp.Height = (FLOAT)_sizeY;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_immediateContext->RSSetViewports(1, &vp);

	_perspectiveMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)_sizeX / (FLOAT)_sizeY, _config.Znear, _config.Zfar);

	return true;
}
void Render::shutdown(){
	SAFE_RELEASE(_depthStencilView);	SAFE_RELEASE(_depthStencil);
	SAFE_RELEASE(_backBuffer);				SAFE_RELEASE(_renderTargetView);
	SAFE_RELEASE(_immediateContext);	SAFE_RELEASE(_swapChain);				SAFE_RELEASE(_device);
}
void Render::update(){
	_beginScene();
	_endScene();
}
bool Render::resizeBuffer(int sizeX, int sizeY){
	_sizeX = sizeX; _sizeY = sizeY;
	_immediateContext->ClearState();
	_immediateContext->OMSetRenderTargets(0, NULL, NULL);

	_depthStencil->Release();	_depthStencilView->Release();	_renderTargetView->Release();	_backBuffer->Release();

	CHECK_RESULT(_swapChain->ResizeBuffers(1, sizeX, sizeY, DXGI_FORMAT_UNKNOWN, 0), "ResizeBuffersError");
	CHECK_RESULT(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer), "Getting backbuffer of swapChain failed");
	CHECK_RESULT(_device->CreateRenderTargetView(_backBuffer, NULL, &_renderTargetView), "Creation of RenderTargetView failed");

	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = _sizeX;	descDepth.Height = _sizeY;
	descDepth.MipLevels = 1;	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;	descDepth.MiscFlags = 0;
	CHECK_RESULT(_device->CreateTexture2D(&descDepth, NULL, &_depthStencil), "Creation of depth stencil texture failed");
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;	descDSV.Texture2D.MipSlice = 0;
	CHECK_RESULT(_device->CreateDepthStencilView(_depthStencil, &descDSV, &_depthStencilView), "Creation of depth stencil view failed");

	D3D11_VIEWPORT vp;	vp.Width = (FLOAT)_sizeX;	vp.Height = (FLOAT)_sizeY;	vp.MinDepth = 0.0f;	vp.MaxDepth = 1.0f;	vp.TopLeftX = 0;	vp.TopLeftY = 0;
	_immediateContext->RSSetViewports(1, &vp);
	_immediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);
	_perspectiveMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)_sizeX / (FLOAT)_sizeY, _config.Znear, _config.Zfar);

	return true;
}
void Render::_beginScene(){
	_immediateContext->ClearRenderTargetView(_renderTargetView, _sceneColor);
	_immediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void Render::_endScene(){
	_swapChain->Present(1, 0);
}
