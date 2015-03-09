#include "Render.h"

#pragma region init&shutdown methods
	Render::Render() {
		errorMessage = ED_UNDEFINED;
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
		CHECK_RESULT(hr, EDR_DEVICE_SWAP_CHAIN);
		CHECK_RESULT(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer), EDR_GET_BACKBUFFER);
		CHECK_RESULT(_device->CreateRenderTargetView(_backBuffer, NULL, &_renderTargetView), EDR_CREATE_RTV);

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
		CHECK_RESULT(_device->CreateTexture2D(&descDepth, NULL, &_depthStencil), EDR_CREATE_DS);

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		CHECK_RESULT(_device->CreateDepthStencilView(_depthStencil, &descDSV, &_depthStencilView), EDR_CREATE_DSV);

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

		CHECK_RESULT(_device->CreateVertexShader(BlobVS_->GetBufferPointer(), BlobVS_->GetBufferSize(), nullptr, &_textureMap.VertexShader), EDR_CREATE_VSHADER);
		CHECK_RESULT(_device->CreatePixelShader(BlobPS_->GetBufferPointer(), BlobPS_->GetBufferSize(), nullptr, &_textureMap.PixelShader), EDR_CREATE_PSHADER);

		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
    _textureMap.VertexStride = 32;
    CHECK_RESULT(
      _device->CreateInputLayout(layout, ARRAYSIZE(layout), BlobVS_->GetBufferPointer(), BlobVS_->GetBufferSize(), &_textureMap.InputLayout), 
      EDR_CREATE_INPUT_LAYOUT);

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.ByteWidth = sizeof(XMFLOAT4X4);
		bd.MiscFlags = 0;
		CHECK_RESULT(_device->CreateBuffer(&bd, NULL, &_bufferViewProj), EDR_CREATE_CB);
	
		ID3D11Buffer* buff_;
		CHECK_RESULT(_device->CreateBuffer(&bd, NULL, &buff_), EDR_CREATE_CB);
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
		CHECK_RESULT(_device->CreateRasterizerState(&RasterDesc, &_rasterizerStates.Solid), EDR_CREATE_RS);
		RasterDesc.CullMode = D3D11_CULL_NONE;
		CHECK_RESULT(_device->CreateRasterizerState(&RasterDesc, &_rasterizerStates.SolidNonCull), EDR_CREATE_RS);
		RasterDesc.FillMode = D3D11_FILL_WIREFRAME;
		CHECK_RESULT(_device->CreateRasterizerState(&RasterDesc, &_rasterizerStates.Wireframe), EDR_CREATE_RS);
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
		CHECK_RESULT(_device->CreateSamplerState(&samplDesc_, &_samplerStates.Linear), EDR_CREATE_SS);
		_immediateContext->PSSetSamplers(0, 1, &_samplerStates.Linear);

		return true;
	}
	void Render::shutdown(){
    clear();

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
		for(uint i = 0; i<_models[MRT_TEXTURE_MAP].size(); i++)
			_renderTextureMapModel(_models[MRT_TEXTURE_MAP][i], &_worldMatrix[MRT_TEXTURE_MAP][i]);

    _endScene();
	}
	void Render::_beginScene(){
		_immediateContext->ClearRenderTargetView(_renderTargetView, _sceneColor);
		_immediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    _immediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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
	void Render::_renderTextureMapModel(Model* model, vector<XMFLOAT4X4*>* matrixs) {
		UINT offset_ = 0;
		_immediateContext->PSSetShaderResources(0, 1, model->getDiffuseMap());
		_immediateContext->IASetVertexBuffers(0, 1, model->getVertexBuffer(), &_textureMap.VertexStride, &offset_);
		_immediateContext->IASetIndexBuffer(model->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
		
		for(unsigned int j = 0; j < matrixs->size(); j++) {
			_mapConstantBufferResource(&_textureMap.Buffers[0], matrixs[0][j]);
			_immediateContext->VSSetConstantBuffers(_textureMap.IndexsOfBuffers[0], 1, &_textureMap.Buffers[0]);
			_immediateContext->DrawIndexed(model->getIndexCount(), 0, 0);
		}
	}
#pragma endregion

#pragma region additional methods
  void Render::clear() {
    for(int i = 0; i < 1; i++) {
      for(uint j = 0; j < _models[i].size(); j++) {
        delete _models[i][j];

        _worldMatrix[i][j].clear();
      }
      _worldMatrix[i].clear();
      _models[i].clear();
    }
  }
	bool Render::resizeBuffer(int sizeX, int sizeY) {
		_sizeX = sizeX; _sizeY = sizeY;
		_immediateContext->ClearState();
		_immediateContext->OMSetRenderTargets(0, NULL, NULL);

		_depthStencil->Release();	_depthStencilView->Release();	_renderTargetView->Release();	_backBuffer->Release();

		CHECK_RESULT(_swapChain->ResizeBuffers(1, sizeX, sizeY, DXGI_FORMAT_UNKNOWN, 0), EDR_RESIZE_BUFFERS);
		CHECK_RESULT(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer), EDR_GET_BACKBUFFER);
		CHECK_RESULT(_device->CreateRenderTargetView(_backBuffer, NULL, &_renderTargetView), EDR_CREATE_RTV);

		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory(&descDepth, sizeof(descDepth));
		descDepth.Width = _sizeX;	descDepth.Height = _sizeY;
		descDepth.MipLevels = 1;	descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;	descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;	descDepth.MiscFlags = 0;
		CHECK_RESULT(_device->CreateTexture2D(&descDepth, NULL, &_depthStencil), EDR_CREATE_DS);
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));	descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;	descDSV.Texture2D.MipSlice = 0;
		CHECK_RESULT(_device->CreateDepthStencilView(_depthStencil, &descDSV, &_depthStencilView), EDR_CREATE_DSV);

		D3D11_VIEWPORT vp;	vp.Width = (FLOAT)_sizeX;	vp.Height = (FLOAT)_sizeY;	vp.MinDepth = 0.0f;	vp.MaxDepth = 1.0f;	vp.TopLeftX = 0;	vp.TopLeftY = 0;
		_immediateContext->RSSetViewports(1, &vp);
		_immediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);
		_perspectiveMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)_sizeX / (FLOAT)_sizeY, _config.Znear, _config.Zfar);

		return true;
	}
	void Render::_mapViewProjectionBufferResource() {
    XMMATRIX viewProjection_ = XMMatrixMultiply(Camera::getInstance().getViewMatrix(), _perspectiveMatrix);
		D3D11_MAPPED_SUBRESOURCE mappedResource_;
    _immediateContext->Map(_bufferViewProj, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource_);
    auto pData = reinterpret_cast<XMFLOAT4X4*>(mappedResource_.pData);
		XMStoreFloat4x4(pData, viewProjection_);
		_immediateContext->Unmap(_bufferViewProj, 0);
		_immediateContext->VSSetConstantBuffers(0, 1, &_bufferViewProj);
	}
	void Render::_mapConstantBufferResource(ID3D11Buffer** buffer, XMFLOAT4X4* matrix) {
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		HRESULT hr = _immediateContext->Map(buffer[0], 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		auto pData = reinterpret_cast<XMFLOAT4X4*>(MappedResource.pData);
		XMStoreFloat4x4(pData, XMLoadFloat4x4(matrix));
		_immediateContext->Unmap(buffer[0], 0);
	}
	bool Render::_compileShaderFromFile(LPCSTR szFileName, const D3D_SHADER_MACRO* pDefines,
		LPCSTR szEntryPoint, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob** ppBlobOut) {
		HRESULT hr; ID3DBlob* pErrorBlob;
		hr = D3DX11CompileFromFile(szFileName, pDefines, NULL, szEntryPoint,
			pTarget, Flags1, Flags2, NULL, ppBlobOut, &pErrorBlob, NULL);
		if(FAILED(hr)) {
			if(pErrorBlob != NULL) {
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
				errorMessage = reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
			}
			else
				errorMessage = EDR_HLSL_PATH;
			if(pErrorBlob) pErrorBlob->Release();
			return false;
		}
		if(pErrorBlob) pErrorBlob->Release();

		return true;
	}
  void Render::_addNewModel(ModelRenderTechnique tech, Model* model, XMFLOAT4X4* worldMatrix) {
    _models[tech].push_back(model);
    vector<XMFLOAT4X4*> matrixsCurrent_;
    matrixsCurrent_.push_back(worldMatrix);
    _worldMatrix[tech].push_back(matrixsCurrent_);
  }
  void Render::_addModel(ModelRenderTechnique tech, int modelIndex, XMFLOAT4X4* worldMatrix) {
    _worldMatrix[tech][modelIndex].push_back(worldMatrix);
  }
  bool Render::createBuffer(D3D11_BUFFER_DESC* bd, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buff) {
    ID3D11Buffer* buf_;
    CHECK_RESULT(_device->CreateBuffer(bd, data, &buf_), EDR_CREATE_BUFFER);
    buff[0] = buf_;
    return true;
  }
  bool Render::createTestTri(XMFLOAT4X4* worldMatrix) {
    int mdlIndex_ = -1;
    for(uint i = 0; i < _models[MRT_TEXTURE_MAP].size(); i++) {
      if(_models[MRT_TEXTURE_MAP][i]->getName() == "testTri") {
        mdlIndex_ = i;
        break;
      }
    }
    if(mdlIndex_ != -1)
      _addModel(MRT_TEXTURE_MAP, mdlIndex_, worldMatrix);
    TextureModel* dummy_ = new TextureModel("testTri");
    Vertex::Default vertexs_[] {
      Vertex::Default(XMFLOAT3(-5.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f)),
        Vertex::Default(XMFLOAT3(5.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f)),
        Vertex::Default(XMFLOAT3(0.0f, 0.0f, 10.0f), XMFLOAT2(0.5f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f))};

    int indexCount_ = 3;
    uint indexs_[] {0, 2, 1};

    D3D11_BUFFER_DESC bd_;
    ZeroMemory(&bd_, sizeof(bd_));
    bd_.Usage = D3D11_USAGE_DEFAULT;
    bd_.ByteWidth = sizeof(Vertex::Default) * indexCount_;
    bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA initData_;
    ZeroMemory(&initData_, sizeof(initData_));
    initData_.pSysMem = vertexs_;

    ID3D11Buffer* vBuf_;
    ID3D11Buffer* iBuf_;
    CHECK_RESULT(createBuffer(&bd_, &initData_, &vBuf_), EDR_CREATE_BUFFER);

    ZeroMemory(&bd_, sizeof(bd_));
    bd_.Usage = D3D11_USAGE_DEFAULT;
    bd_.ByteWidth = sizeof(UINT)* indexCount_;
    bd_.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ZeroMemory(&initData_, sizeof(initData_));
    initData_.pSysMem = indexs_;
    CHECK_RESULT(createBuffer(&bd_, &initData_, &iBuf_), EDR_CREATE_BUFFER);

    dummy_->setVertexBuffer(vBuf_);
    dummy_->setIndexBuffer(iBuf_, indexCount_);

    _addNewModel(MRT_TEXTURE_MAP, dummy_, worldMatrix);

    return true;
  }
  bool Render::addModel(string fileName, XMFLOAT4X4* worldMatrix) {
    OPEN_STREAM(fileName, "r");
    // TODO: Need to define the ModelRenderTechnique!! for now only one tech ^)
    ModelRenderTechnique tech_ = MRT_TEXTURE_MAP;
    CLOSE_STREAM();
    int mdlIndex_ = -1;
    for(uint i = 0; i < _models[tech_].size(); i++) {
      if(_models[tech_][i]->getName() == fileName) {
        mdlIndex_ = i;
        break;
      }
    }
    if(mdlIndex_ != -1)  {
      _addModel(tech_, mdlIndex_, worldMatrix);
      return true;
    }

    //TODO: switch for various techniques
    TextureModel* mdl_ = new TextureModel(fileName);
    OPEN_STREAM(fileName, "r");
    int numV_ = 0;  int numF_ = 0; int numTV_ = 0;
    READ_INT(&numV_); READ_INT(&numF_); READ_INT(&numTV_);
    vector<XMFLOAT3> verts_;  vector<XMFLOAT2> tVerts_;   vector<XMFLOAT3> norms_;
    vector<int3> vertFaces;   vector<int3> tVertFaces;
    
    for(int i = 0; i < numV_; i++) {
      XMFLOAT3 float3_;
      READ_FLOAT(&float3_.x); READ_FLOAT(&float3_.z); READ_FLOAT(&float3_.y);
      verts_.push_back(float3_);
      READ_FLOAT(&float3_.x); READ_FLOAT(&float3_.z); READ_FLOAT(&float3_.y);
      norms_.push_back(float3_);
    }

    for(int i = 0; i < numF_; i++) {
      int3 int3_;
      READ_INT(&int3_.x);	READ_INT(&int3_.z);	READ_INT(&int3_.y);
      vertFaces.push_back(int3_);
    }
    for(int i = 0; i < numTV_; i++) {
      XMFLOAT2 float2_; float left_;
      READ_FLOAT(&float2_.x); READ_FLOAT(&float2_.y); READ_FLOAT(&left_);
      tVerts_.push_back(float2_);
    }
    for(int i = 0; i < numF_; i++) {
      int3 int3_;
      READ_INT(&int3_.x);	READ_INT(&int3_.z);	READ_INT(&int3_.y);
      tVertFaces.push_back(int3_);
    }
    vector<Vertex::Default> simpleVerts_;
    vector<Vertex::Default> optimizedVerts_;
    unsigned int countInds_ = 0;
    for(int i = 0; i < numF_; i++) {
      simpleVerts_.push_back(Vertex::Default(verts_[vertFaces[i].x], tVerts_[tVertFaces[i].x], norms_[vertFaces[i].x]));
      simpleVerts_.push_back(Vertex::Default(verts_[vertFaces[i].y], tVerts_[tVertFaces[i].y], norms_[vertFaces[i].y]));
      simpleVerts_.push_back(Vertex::Default(verts_[vertFaces[i].z], tVerts_[tVertFaces[i].z], norms_[vertFaces[i].z]));
    }
    countInds_ = simpleVerts_.size();
    verts_.clear();	tVerts_.clear();	norms_.clear();	vertFaces.clear();	tVertFaces.clear();
    unsigned int* indsForIndexBuffer_ = new unsigned int[countInds_];

    for(unsigned int i = 0; i < countInds_; i++) indsForIndexBuffer_[i] = i;
    bool write = true;
    optimizedVerts_.push_back(simpleVerts_[0]);
    for(unsigned int i = 1; i < countInds_; i++) {
      write = true;
      for(unsigned int j = 0; j < optimizedVerts_.size(); j++) {
        if(simpleVerts_[i].position.x == optimizedVerts_[j].position.x && simpleVerts_[i].texCoords.x == optimizedVerts_[j].texCoords.x &&
          simpleVerts_[i].position.y == optimizedVerts_[j].position.y && simpleVerts_[i].texCoords.y == optimizedVerts_[j].texCoords.y &&
          simpleVerts_[i].position.z == optimizedVerts_[j].position.z) {
          write = false;
          indsForIndexBuffer_[i] = j;
        }
      }
      if(write) {
        optimizedVerts_.push_back(simpleVerts_[i]);
        indsForIndexBuffer_[i] = optimizedVerts_.size() - 1;
      }
    }
    Vertex::Default* vertexs_ = new Vertex::Default[optimizedVerts_.size()];
    for(unsigned int i = 0; i < optimizedVerts_.size(); i++) vertexs_[i] = optimizedVerts_[i];

    CLOSE_STREAM();

    D3D11_BUFFER_DESC bd_;
    ZeroMemory(&bd_, sizeof(bd_));
    bd_.Usage = D3D11_USAGE_DEFAULT;
    bd_.ByteWidth = sizeof(Vertex::Default) * optimizedVerts_.size();
    bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA initData_;
    ZeroMemory(&initData_, sizeof(initData_));
    initData_.pSysMem = vertexs_;

    ID3D11Buffer* vBuf_;
    ID3D11Buffer* iBuf_;
    CHECK_RESULT(createBuffer(&bd_, &initData_, &vBuf_), EDR_CREATE_BUFFER);

    ZeroMemory(&bd_, sizeof(bd_));
    bd_.Usage = D3D11_USAGE_DEFAULT;
    bd_.ByteWidth = sizeof(UINT)* countInds_;
    bd_.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ZeroMemory(&initData_, sizeof(initData_));
    initData_.pSysMem = indsForIndexBuffer_;
    CHECK_RESULT(createBuffer(&bd_, &initData_, &iBuf_), EDR_CREATE_BUFFER);

    mdl_->setVertexBuffer(vBuf_);
    mdl_->setIndexBuffer(iBuf_, countInds_);

    ID3D11ShaderResourceView* texture_;
    if(!createTexture(fileName.substr(0, fileName.length() - 3) + "dds", &texture_))  {
      errorMessage = "Texture create error";
      return false;
    }

    mdl_->setDiffuseMap(texture_);

    _addNewModel(tech_, mdl_, worldMatrix);

    verts_.clear();  tVerts_.clear();  norms_.clear();
    vertFaces.clear();  tVertFaces.clear();
    simpleVerts_.clear();  optimizedVerts_.clear();

    return true;
  }
  bool Render::createTexture(string fileName, ID3D11ShaderResourceView** texture) {
    D3DX11_IMAGE_LOAD_INFO ILI;
    HRESULT hr;
    D3DX11CreateShaderResourceViewFromFile(_device, fileName.c_str(), NULL, NULL, &texture[0], &hr);
    if(SUCCEEDED(hr))return true;
    return false;
  }
  bool Render::createTexture(string fileName, D3DX11_IMAGE_LOAD_INFO* ili, ID3D11ShaderResourceView** texture) {
    HRESULT hr;
    D3DX11CreateShaderResourceViewFromFile(_device, fileName.c_str(), ili, NULL, &texture[0], &hr);
    if(SUCCEEDED(hr))return true;
    return false;
  }
#pragma endregion