#include "D3dRender.h"
#define checkResult(hres, msg) if(FAILED(hres)){ErrorMessage = msg;return false; }

D3dRender::D3dRender()
{
	ErrorMessage = "D3dRender";
	_mayInitialized = false;
	_sceneColor = new float[4] { 0.0f, 0.125f, 0.3f, 1.0f };
}
void D3dRender::shutdown()
{

}
void D3dRender::setInitialize(HWND hwnd, int sizeX, int sizeY)
{
	_hwnd = hwnd;
	_sizeX = sizeX;
	_sizeY = sizeY;
	_mayInitialized = true;
}
bool D3dRender::initialize()
{
	if(!_mayInitialized) { ErrorMessage = "Set hwnd & size of render before initialize d3dRender"; return false; }
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
	sd.OutputWindow = _hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for(UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, _driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &_swapChain, &_device, &_featureLevel, &_immediateContext);
		if(SUCCEEDED(hr))
			break;
	}
	checkResult(hr, "Creation of device & swapChain failed");
	checkResult(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer),"Getting backbuffer of swapChain failed");
	checkResult(_device->CreateRenderTargetView(_backBuffer, NULL, &_renderTargetView),"Creation of RenderTargetView failed");
	/*if(FAILED(hr))
	{
		ErrorMessage = "Creation of device & swapChain failed";
		return false;
	}

	if(FAILED(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer)))
	{
		ErrorMessage = "Getting backbuffer of swapChain failed";
		return false;
	}
	if(FAILED(_device->CreateRenderTargetView(_backBuffer, NULL, &_renderTargetView)))
	{
		ErrorMessage = "Creation of RenderTargetView failed";
		return false;
	}*/

	_backBuffer->GetDesc(&_tex2DDescPICK);
	_tex2DDescPICK.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	_tex2DDescPICK.Usage = D3D11_USAGE_STAGING;
	_tex2DDescPICK.BindFlags = 0;
	_tex2DDescPICK.Width = 1;
	_tex2DDescPICK.Height = 1;

	checkResult(_device->CreateTexture2D(&_tex2DDescPICK, NULL, &_backReadFromPICK),"Creation of texture for picking failed");

	/*if(FAILED(_device->CreateTexture2D(&_tex2DDescPICK, NULL, &_backReadFromPICK)))
	{
		ErrorMessage = "Creation of texture for picking failed";
		return false;
	}*/

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

	checkResult(_device->CreateTexture2D(&descDepth, NULL, &_depthStencil), "Creation of depth stencil texture failed");
	/*if(FAILED(_device->CreateTexture2D(&descDepth, NULL, &_depthStencil)))
	{
		ErrorMessage = "Creation of depth stencil texture failed";
		return false;
	}*/

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	checkResult(_device->CreateDepthStencilView(_depthStencil, &descDSV, &_depthStencilView), "Creation of depth stencil view failed");
	/*if(FAILED(_device->CreateDepthStencilView(_depthStencil, &descDSV, &_depthStencilView)))
	{
		ErrorMessage = "Creation of depth stencil view failed";
		return false;
	}*/
	_immediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)_sizeX;
	vp.Height = (FLOAT)_sizeY;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_immediateContext->RSSetViewports(1, &vp);

	_PerspectiveMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)_sizeX / (FLOAT)_sizeY, 0.01f, 1000.0f);
	_OrthograficMatrix = XMMatrixOrthographicLH((FLOAT)_sizeX, (FLOAT)_sizeY, -100.0f, 1000.0f);
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	checkResult(_device->CreateBuffer(&bd, NULL, &_bViewProj), "Creation of constant buffer for ViewProj failed");
	/*if(FAILED(_device->CreateBuffer(&bd, NULL, &CB_Per_Frame)))
	{
		ErrorMessage = "Creation of constant buffer for ViewProj failed";
		return false;
	}*/
	return true;
}
