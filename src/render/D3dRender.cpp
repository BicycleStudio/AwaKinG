#include "D3dRender.h"

D3dRender::D3dRender()
{
	ErrorMessage = "D3dRender";
	_mayInitialized = false;
	_sceneColor = new float[4] { 0.0f, 0.125f, 0.3f, 1.0f };
	
	_device = 0;
	_immediateContext = 0;
	_swapChain = 0;
	_renderTargetView = 0;
	_backBuffer = 0;
	_depthStencil = 0;
	_depthStencilView = 0;
	ViewMatrix = 0;
	
	_bViewProj = 0;
	_ssLinear = 0;

	_TextureMap.VS = 0;
	_TextureMap.PS = 0;
	_TextureMap.IL = 0;
	_TextureMap.Buffer = 0;

	_rs.NonCull = 0;
	_rs.Solid = 0;
	_rs.Wireframe = 0;
}
void D3dRender::shutdown()
{
	safeRelease(_TextureMap.VS);
	safeRelease(_TextureMap.PS);
	safeRelease(_TextureMap.IL);
	safeRelease(_TextureMap.Buffer);

	safeRelease(_rs.NonCull);
	safeRelease(_rs.Solid);
	safeRelease(_rs.Wireframe);

	safeRelease(_depthStencilView);
	safeRelease(_depthStencil);
	safeRelease(_backBuffer);
	safeRelease(_renderTargetView);
	safeRelease(_immediateContext);
	safeRelease(_swapChain);
	safeRelease(_device);
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

	_backBuffer->GetDesc(&_tex2DDescPICK);
	_tex2DDescPICK.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	_tex2DDescPICK.Usage = D3D11_USAGE_STAGING;
	_tex2DDescPICK.BindFlags = 0;
	_tex2DDescPICK.Width = 1;
	_tex2DDescPICK.Height = 1;
	checkResult(_device->CreateTexture2D(&_tex2DDescPICK, NULL, &_backReadFromPICK),"Creation of texture for picking failed");

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

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	checkResult(_device->CreateDepthStencilView(_depthStencil, &descDSV, &_depthStencilView), "Creation of depth stencil view failed");
	
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
	
	if(!initializeShaders()) return false;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.MiscFlags = 0;
	checkResult(_device->CreateBuffer(&bd, NULL, &_bViewProj), "Creation of constant buffer for ViewProj failed");

	D3D11_RASTERIZER_DESC RasterDesc;
	ZeroMemory(&RasterDesc, sizeof(D3D11_RASTERIZER_DESC));
	RasterDesc.FillMode = D3D11_FILL_SOLID;
	RasterDesc.CullMode = D3D11_CULL_BACK;
	RasterDesc.DepthClipEnable = TRUE;
	checkResult(_device->CreateRasterizerState(&RasterDesc, &_rs.Solid),
		"Creation of Solid RS failed");
	RasterDesc.CullMode = D3D11_CULL_NONE;
	checkResult(_device->CreateRasterizerState(&RasterDesc, &_rs.NonCull),
		"Creation of NonCull RS failed");
	RasterDesc.FillMode = D3D11_FILL_WIREFRAME;
	checkResult(_device->CreateRasterizerState(&RasterDesc, &_rs.Wireframe),
		"Creation of Wireframe RS failed");

	return true;
}
bool D3dRender::initializeShaders()
{
	ID3DBlob* BlobVS_ = nullptr;
	ID3DBlob* BlobPS_ = nullptr;

	if(!compileShaderFromFile(L"fx/TextureMap.hlsl", nullptr, "VS", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR, 0, &BlobVS_)) return false;
	if(!compileShaderFromFile(L"fx/TextureMap.hlsl", nullptr, "PS", "ps_5_0", D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR, 0, &BlobPS_)) return false;
	
	checkResult(_device->CreateVertexShader(BlobVS_->GetBufferPointer(), BlobVS_->GetBufferSize(), nullptr, &_TextureMap.VS),
		"Creation of Texture_Mapping vertex shader failed");
	checkResult(_device->CreatePixelShader(BlobPS_->GetBufferPointer(), BlobPS_->GetBufferSize(), nullptr, &_TextureMap.PS),
		"Creation of Texture_Mapping pixel shader failed");
	
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	checkResult(_device->CreateInputLayout(layout, ARRAYSIZE(layout), BlobVS_->GetBufferPointer(), BlobVS_->GetBufferSize(), &_TextureMap.IL),
		"Creation of Texture_Mapping input layout failed");

	_TextureMap.VertexStride = 32;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.MiscFlags = 0;
	checkResult(_device->CreateBuffer(&bd, NULL, &_TextureMap.Buffer), "Creation of constant buffer for ViewProj failed");
	_TextureMap.IndexOfBuffer = 1;

	safeRelease(BlobVS_);
	safeRelease(BlobPS_);

	return true;
}
void D3dRender::render()
{
	beginScene();

	D3D11_MAPPED_SUBRESOURCE MappedResource;
	_immediateContext->Map(_bViewProj, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
	auto pData = reinterpret_cast<ConstantBuffer*>(MappedResource.pData);
	XMMATRIX mm = XMMatrixMultiply(XMLoadFloat4x4(ViewMatrix), _PerspectiveMatrix);
	XMStoreFloat4x4(&pData->matr, mm);
	_immediateContext->Unmap(_bViewProj, 0);
	_immediateContext->VSSetConstantBuffers(0, 1, &_bViewProj);

	prepareToRenderTechnique(_TextureMap);
	/*for(int i=0; i< _models.size(); i++)*/
		renderTextureMapModel(/*model*/);

	endScene();
}
void D3dRender::renderTextureMapModel(/*model*/)
{
	D3D11_MAPPED_SUBRESOURCE MappedResource;
	_immediateContext->Map(_TextureMap.Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
	auto pData = reinterpret_cast<ConstantBuffer*>(MappedResource.pData);
	//XMStoreFloat4x4(&pData->matr, model->WorldMatrix);
	_immediateContext->Unmap(_TextureMap.Buffer, 0);
	_immediateContext->VSSetConstantBuffers(_TextureMap.IndexOfBuffer, 1, &_TextureMap.Buffer);

	//_immediateContext->PSSetShaderResources(0, 1,model->Texture);
	//
	//UINT Stride = _TextureMap.VertexStride;
	//UINT Offset = 0;
	//_immediateContext->IASetVertexBuffers(0, 1, &model->VBuffer, &Stride, &Offset);
	//_immediateContext->IASetIndexBuffer(model->IBuffer,DXGI_FORMAT_R32_UINT, Offset);
	//_immediateContext->DrawIndexed(IndexCount, 0, 0);
}
void D3dRender::prepareToRenderTechnique(TechniqueVP tech)
{
	_immediateContext->VSSetShader(tech.VS, nullptr, 0);
	_immediateContext->PSSetShader(tech.PS, nullptr, 0);
	_immediateContext->IASetInputLayout(tech.IL);
	_immediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
void D3dRender::beginScene()
{
	_immediateContext->ClearRenderTargetView(_renderTargetView, _sceneColor);
	_immediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
void D3dRender::endScene()
{
	_swapChain->Present(0, 0);
}
bool D3dRender::compileShaderFromFile(LPCWSTR pFileName, const D3D_SHADER_MACRO* pDefines,
	LPCSTR pEntrypoint, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob** ppCode)
{
	HRESULT hr;

#if defined( DEBUG ) || defined( _DEBUG )
	Flags1 |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob = nullptr;

#if D3D_COMPILER_VERSION >= 46

	hr = D3DCompileFromFile(pFileName, pDefines, D3D_COMPILE_STANDARD_FILE_INCLUDE, pEntrypoint, pTarget, Flags1, Flags2, ppCode, &pErrorBlob);

#else

	ScopedHandle hFile(safe_handle(CreateFileW(str, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr)));

	if(!hFile)
		return HRESULT_FROM_WIN32(GetLastError());

	LARGE_INTEGER FileSize = { 0 };

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
	FILE_STANDARD_INFO fileInfo;
	if(!GetFileInformationByHandleEx(hFile.get(), FileStandardInfo, &fileInfo, sizeof(fileInfo)))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}
	FileSize = fileInfo.EndOfFile;
#else
	GetFileSizeEx(hFile.get(), &FileSize);
#endif

	if(!FileSize.LowPart || FileSize.HighPart > 0)
		return E_FAIL;

	std::unique_ptr<char[]> fxData;
	fxData.reset(new (std::nothrow) char[FileSize.LowPart]);
	if(!fxData)
		return E_OUTOFMEMORY;

	DWORD BytesRead = 0;
	if(!ReadFile(hFile.get(), fxData.get(), FileSize.LowPart, &BytesRead, nullptr))
		return HRESULT_FROM_WIN32(GetLastError());

	if(BytesRead < FileSize.LowPart)
		return E_FAIL;

	char pSrcName[MAX_PATH];
	int result = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, str, -1, pSrcName, MAX_PATH, nullptr, FALSE);
	if(!result)
		return E_FAIL;

	const CHAR* pstrName = strrchr(pSrcName, '\\');
	if(!pstrName)
	{
		pstrName = pSrcName;
	}
	else
	{
		pstrName++;
	}

	std::unique_ptr<CIncludeHandler> includes(new (std::nothrow) CIncludeHandler);
	if(!includes)
		return E_OUTOFMEMORY;

	includes->SetCWD(str);

	hr = D3DCompile(fxData.get(), BytesRead, pstrName, pDefines, includes.get(),
		pEntrypoint, pTarget, Flags1, Flags2,
		ppCode, &pErrorBlob);

#endif

#pragma warning( suppress : 6102 )
	if(pErrorBlob)
	{
		OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
		ErrorMessage = reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
		pErrorBlob->Release();
		return false;
	}
	return true;
}