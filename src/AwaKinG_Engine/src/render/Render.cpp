#include "Render.h"

#pragma region init&shutdown methods
	Render::Render() {
		_sceneColor = new float[4] { 0.0f, 0.125f, 0.3f, 1.0f };
		_device = 0;
		_immediateContext = 0;
		_swapChain = 0;
		_renderTargetView = 0;
		_backBuffer = 0;
		_depthStencil = 0;
		_depthStencilView = 0;

		_bufferViewProj = 0;
		_textureMap = TechniqueBuffers();
		_rasterizerStates = RasterizerState(); 
		_samplerStates = SamplerState();
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

		if(!_initializeRasterizerStates()) return false;
		if(!_initializeSamplerStates()) return false;
		if(!_initializeShaders()) return false;
		return true;
	}
	bool Render::_initializeShaders() {
		ID3DBlob* BlobVS_ = nullptr;	ID3DBlob* BlobPS_ = nullptr;
		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	#ifdef _DLL_EXPORT
		string currentShaderPath_ = "../../../../fx/TextureMap.hlsl";
	#else 
		string currentShaderPath_ = "../../fx/TextureMap.hlsl";
	#endif
		if(!_compileShaderFromFile(currentShaderPath_.c_str(), nullptr, "VS", "vs_5_0", flags, 0, &BlobVS_)) return false;
		if(!_compileShaderFromFile(currentShaderPath_.c_str(), nullptr, "PS", "ps_5_0", flags, 0, &BlobPS_)) return false;

		CHECK_RESULT(_device->CreateVertexShader(BlobVS_->GetBufferPointer(), BlobVS_->GetBufferSize(), nullptr, &_textureMap.VertexShader),
			"Creation of Texture_Mapping vertex shader failed");
		CHECK_RESULT(_device->CreatePixelShader(BlobPS_->GetBufferPointer(), BlobPS_->GetBufferSize(), nullptr, &_textureMap.PixelShader),
			"Creation of Texture_Mapping pixel shader failed");

		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.ByteWidth = sizeof(XMFLOAT4X4);
		bd.MiscFlags = 0;
		CHECK_RESULT(_device->CreateBuffer(&bd, NULL, &_bufferViewProj), "Creation of constant buffer ViewProjection failed");
	
		ID3D11Buffer* buff_;
		CHECK_RESULT(_device->CreateBuffer(&bd, NULL, &buff_), "Creation of constant buffer failed");
		_textureMap.Buffers.push_back(buff_);	
		_textureMap.IndexsOfBuffers.push_back(1);

		SAFE_RELEASE(BlobVS_);
		SAFE_RELEASE(BlobPS_);

		return true;
	}
	bool Render::_initializeRasterizerStates() {
		D3D11_RASTERIZER_DESC RasterDesc;
		ZeroMemory(&RasterDesc, sizeof(D3D11_RASTERIZER_DESC));
		RasterDesc.FillMode = D3D11_FILL_SOLID;
		RasterDesc.CullMode = D3D11_CULL_BACK;
		RasterDesc.DepthClipEnable = TRUE;
		CHECK_RESULT(_device->CreateRasterizerState(&RasterDesc, &_rasterizerStates.Solid),
			"Creation of Solid RS failed");
		RasterDesc.CullMode = D3D11_CULL_NONE;
		CHECK_RESULT(_device->CreateRasterizerState(&RasterDesc, &_rasterizerStates.SolidNonCull),
			"Creation of NonCull RS failed");
		RasterDesc.FillMode = D3D11_FILL_WIREFRAME;
		CHECK_RESULT(_device->CreateRasterizerState(&RasterDesc, &_rasterizerStates.Wireframe),
			"Creation of Wireframe RS failed");
		_immediateContext->RSSetState(_rasterizerStates.Solid);

		return true;
	}
	bool Render::_initializeSamplerStates() {
		D3D11_SAMPLER_DESC samplDesc_;
		samplDesc_.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplDesc_.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplDesc_.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplDesc_.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplDesc_.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplDesc_.MaxAnisotropy = 16;
		samplDesc_.MipLODBias = 0;
		samplDesc_.MinLOD = 0;
		samplDesc_.MaxLOD = 16;
		CHECK_RESULT(_device->CreateSamplerState(&samplDesc_, &_samplerStates.Linear),
			"Creation of Wireframe RS failed");
		_immediateContext->PSSetSamplers(0, 1, &_samplerStates.Linear);

		return true;
	}
	void Render::shutdown(){
		_textureMap.release();
		_rasterizerStates.release();
		_samplerStates.release();
		SAFE_RELEASE(_bufferViewProj);
	
		SAFE_RELEASE(_depthStencilView);	SAFE_RELEASE(_depthStencil);
		SAFE_RELEASE(_backBuffer);				SAFE_RELEASE(_renderTargetView);
		SAFE_RELEASE(_immediateContext);	SAFE_RELEASE(_swapChain);				SAFE_RELEASE(_device);
	}
#pragma endregion

#pragma region render methods
	void Render::update() {
		_beginScene();

		_prepareToRenderTechnique(_textureMap);
		/*
		for(int i=0; i<textureMapModels.size(); i++)
			_renderTextureMapModel(&_matrixs[ART_TEXTURE_MAP][i]);

		_prepareToRenderTechnique(_bumpMap);
		for(int i=0; i<textureMapModels.size(); i++)
			_renderTextureMapModel(&_matrixs[ART_BUMP_MAP][i]);
		*/
		_endScene();
	}
	void Render::_beginScene(){
		_immediateContext->ClearRenderTargetView(_renderTargetView, _sceneColor);
		_immediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		_mapViewProjectionBufferResource();
	}
	void Render::_endScene(){
		_swapChain->Present(1, 0);
	}
	void Render::_prepareToRenderTechnique(Technique tech) {
		_immediateContext->VSSetShader(tech.VertexShader, nullptr, 0);
		_immediateContext->PSSetShader(tech.PixelShader, nullptr, 0);
		_immediateContext->IASetInputLayout(tech.InputLayout);
	}
	void Render::_renderTextureMapModel(/*ModelEx* model,*/ vector<XMFLOAT4X4*>* matrixs) {
		/*UINT offset_ = 0;
		_immediateContext->PSSetShaderResources(0, 1, model->getTexture());
		_immediateContext->IASetVertexBuffers(0, 1, model->getVertexBuffer(), &_textureMap.VertexStride, &offset_);
		_immediateContext->IASetIndexBuffer(model->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

		for(unsigned int j = 0; j < matrixs->size(); j++) {
			_mapConstantBufferResource(&_textureMap.Buffer[0], matrixs[0][j]);
			_immediateContext->VSSetConstantBuffers(_textureMap.IndexOfBuffer[0], 1, &_textureMap.Buffer[0]);
			_immediateContext->DrawIndexed(model->getIndexCount(), 0, 0);
		}*/
	}
#pragma endregion

#pragma region additional methods
	bool Render::resizeBuffer(int sizeX, int sizeY) {
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
	void Render::_mapViewProjectionBufferResource() {
		XMMATRIX viewProjection_ = _perspectiveMatrix; //XMMatrixMultiply(XMLoadFloat4x4(Camera::getInstance().getViewMatrixPointer()), _PerspectiveMatrix);
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		_immediateContext->Map(_bufferViewProj, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		auto pData = reinterpret_cast<XMFLOAT4X4*>(MappedResource.pData);
		XMStoreFloat4x4(pData, viewProjection_);
		_immediateContext->Unmap(_bufferViewProj, 0);
		_immediateContext->VSSetConstantBuffers(0, 1, &_bufferViewProj);
		//	_immediateContext->GSSetConstantBuffers(0, 1, &_bViewProj);
		//	_immediateContext->CSSetConstantBuffers(0, 1, &_bViewProj);
		//	_immediateContext->PSSetConstantBuffers(0, 1, &_bViewProj);
		//	_immediateContext->HSSetConstantBuffers(0, 1, &_bViewProj);
		//	_immediateContext->DSSetConstantBuffers(0, 1, &_bViewProj);
	}
	bool Render::_compileShaderFromFile(LPCSTR szFileName, const D3D_SHADER_MACRO* pDefines,
		LPCSTR szEntryPoint, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob** ppBlobOut) {
		HRESULT hr; ID3DBlob* pErrorBlob;
		hr = D3DX11CompileFromFile(szFileName, pDefines, NULL, szEntryPoint,
			pTarget, Flags1, Flags2, NULL, ppBlobOut, &pErrorBlob, NULL);
		if(FAILED(hr)) {
			if(pErrorBlob != NULL)
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
			errorMessage = reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
			if(pErrorBlob) pErrorBlob->Release();
			return false;
		}
		if(pErrorBlob) pErrorBlob->Release();

		return true;
	}
#pragma endregion