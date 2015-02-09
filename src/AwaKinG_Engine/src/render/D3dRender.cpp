#include "D3dRender.h"
#define ReadPixelFromMappedSubResource(x, y)       ( *( (RGBQUAD *)((BYTE *)MappedSubResource.pData + (y)*MappedSubResource.RowPitch + (x)*sizeof(DWORD)) ) )

#pragma region mainFunctions
	D3dRender::D3dRender()
	{
		ErrorMessage = "D3dRender";
		_mayInitialized = false;
		_sceneColor = new float[4] { 0.0f, 0.125f, 0.3f, 1.0f };
		_pickColor = new float[4] { 1.0f, 1.0f, 1.0f, 1.0f };

		_device = 0;
		_immediateContext = 0;
		_swapChain = 0;
		_renderTargetView = 0;
		_backBuffer = 0;
		_depthStencil = 0;
		_depthStencilView = 0;
	
		_bViewProj = 0;
		_ssLinear = 0;

		_textureMap.VS = 0;
		_textureMap.PS = 0;
		_textureMap.IL = 0;

		_terrainTech.VS = 0;
		_terrainTech.PS = 0;
		_terrainTech.IL = 0;
	
		_rs.NonCull = 0;
		_rs.Solid = 0;
		_rs.Wireframe = 0;

		vector<ModelEx*> systemModels_;
		vector<ModelEx*> textureModels_;
		vector<ModelEx*> bumpModels_;
		_models.push_back(systemModels_);
		_models.push_back(textureModels_);
		_models.push_back(bumpModels_);
		vector<vector<XMFLOAT4X4*>> worldMatrixsSystemModels_;
		vector<vector<XMFLOAT4X4*>> worldMatrixsTextureModels_;
		vector<vector<XMFLOAT4X4*>> worldMatrixsbumpModels_;
		_worldMatrixs.push_back(worldMatrixsSystemModels_);
		_worldMatrixs.push_back(worldMatrixsTextureModels_);
		_worldMatrixs.push_back(worldMatrixsbumpModels_);

		_renderTerrainQuadTree = true; 
		_renderTerrainWireframe = true; 
	}
	void D3dRender::shutdown()
	{
		for(unsigned int i = 0; i < _models.size(); i++)
		{
			for(unsigned int j = 0; j < _models[i].size(); j++)
			{
				_models[i][j]->shutdown();
				delete _models[i][j];
			}
			_models[i].clear();
		}
		_models.clear();

		for(unsigned int i = 0; i < _worldMatrixs.size(); i++)
		{
			for(unsigned int j = 0; j < _worldMatrixs[i].size(); j++)
			{
				for(unsigned int k = 0; k < _worldMatrixs[i][j].size(); k++)
				{
					delete _worldMatrixs[i][j][k];
				}
				_worldMatrixs[i][j].clear();
			}
			_worldMatrixs[i].clear();
		}
		_worldMatrixs.clear();

		for(unsigned int j = 0; j < _terrainTiles.size(); j++)
		{
			_terrainTiles[j]->shutdown();
			delete _terrainTiles[j];
		}
		_terrainTiles.clear();

		if(_textureMap.Buffer.size())		safeRelease(_textureMap.Buffer[0]);

		safeRelease(_textureMap.VS);		safeRelease(_textureMap.PS);		safeRelease(_textureMap.IL);		
		safeRelease(_terrainTech.VS);		safeRelease(_terrainTech.PS);		safeRelease(_terrainTech.IL);	
		safeRelease(_rs.NonCull);				safeRelease(_rs.Solid);					safeRelease(_rs.Wireframe);
		safeRelease(_depthStencilView);	safeRelease(_depthStencil);
		safeRelease(_backBuffer);				safeRelease(_renderTargetView);
		safeRelease(_immediateContext);	safeRelease(_swapChain);				safeRelease(_device);
	}
	void D3dRender::setInitialize(HWND hwnd, int sizeX, int sizeY, string shaderPath)
	{
		_shaderPath = shaderPath;
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
			if(SUCCEEDED(hr))			break;
		}
		checkResult(hr, "Creation of device & swapChain failed");
		checkResult(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer),"Getting backbuffer of swapChain failed");
		checkResult(_device->CreateRenderTargetView(_backBuffer, NULL, &_renderTargetView),"Creation of RenderTargetView failed");

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

		_PerspectiveMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)_sizeX / (FLOAT)_sizeY, _config.Znear, _config.Zfar);
		XMStoreFloat4x4(&_perspectiveMatrix, _PerspectiveMatrix);
		_OrthograficMatrix = XMMatrixOrthographicLH((FLOAT)_sizeX, (FLOAT)_sizeY, -_config.Zfar, _config.Zfar);

		if(!_initializeShaders()) return false;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.ByteWidth = sizeof(ConstantBufferMatrix);
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
		_immediateContext->RSSetState(_rs.Solid);

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
		checkResult(_device->CreateSamplerState(&samplDesc_, &_ssDefault),
			"Creation of Wireframe RS failed");
			//BorderColor = SharpDX.Color.Black,
		_immediateContext->PSSetSamplers(0, 1, &_ssDefault);

		_createSystemBox();
		return true;
	}
	bool D3dRender::_initializeShaders()
	{
		_shaderPath;
		ID3DBlob* BlobVS_ = nullptr;	ID3DBlob* BlobPS_ = nullptr;
		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

		string currentShaderPath_ = _shaderPath + "TextureMap.hlsl";
		if(!_compileShaderFromFile(currentShaderPath_.c_str(), nullptr, "VS", "vs_5_0", flags, 0, &BlobVS_)) return false;
		if(!_compileShaderFromFile(currentShaderPath_.c_str(), nullptr, "PS", "ps_5_0", flags, 0, &BlobPS_)) return false;
	
		checkResult(_device->CreateVertexShader(BlobVS_->GetBufferPointer(), BlobVS_->GetBufferSize(), nullptr, &_textureMap.VS),
			"Creation of Texture_Mapping vertex shader failed");
		checkResult(_device->CreatePixelShader(BlobPS_->GetBufferPointer(), BlobPS_->GetBufferSize(), nullptr, &_textureMap.PS),
			"Creation of Texture_Mapping pixel shader failed");

		const D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		checkResult(_device->CreateInputLayout(layout, ARRAYSIZE(layout), BlobVS_->GetBufferPointer(), BlobVS_->GetBufferSize(), &_textureMap.IL),
			"Creation of Texture_Mapping input layout failed");

		if(!_compileShaderFromFile(currentShaderPath_.c_str(), nullptr, "VSTerrain", "vs_5_0", flags, 0, &BlobVS_)) return false;
		if(!_compileShaderFromFile(currentShaderPath_.c_str(), nullptr, "PSTerrain", "ps_5_0", flags, 0, &BlobPS_)) return false;

		checkResult(_device->CreateVertexShader(BlobVS_->GetBufferPointer(), BlobVS_->GetBufferSize(), nullptr, &_terrainTech.VS),
			"Creation of Texture_Mapping vertex shader failed");
		checkResult(_device->CreatePixelShader(BlobPS_->GetBufferPointer(), BlobPS_->GetBufferSize(), nullptr, &_terrainTech.PS),
			"Creation of Texture_Mapping pixel shader failed");
		_terrainTech.IL = _textureMap.IL;
		_textureMap.VertexStride = 32; _terrainTech.VertexStride = 32;

		
		if(!_compileShaderFromFile(currentShaderPath_.c_str(), nullptr, "VSSystemModel", "vs_5_0", flags, 0, &BlobVS_)) return false;
		if(!_compileShaderFromFile(currentShaderPath_.c_str(), nullptr, "PSSystemModel", "ps_5_0", flags, 0, &BlobPS_)) return false;

		checkResult(_device->CreateVertexShader(BlobVS_->GetBufferPointer(), BlobVS_->GetBufferSize(), nullptr, &_colorMap.VS),
			"Creation of Texture_Mapping vertex shader failed");
		checkResult(_device->CreatePixelShader(BlobPS_->GetBufferPointer(), BlobPS_->GetBufferSize(), nullptr, &_colorMap.PS),
			"Creation of Texture_Mapping pixel shader failed");
		
		const D3D11_INPUT_ELEMENT_DESC layoutColor[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		checkResult(_device->CreateInputLayout(layoutColor, ARRAYSIZE(layoutColor), BlobVS_->GetBufferPointer(), BlobVS_->GetBufferSize(), &_colorMap.IL),
			"Creation of Texture_Mapping input layout failed");
		_colorMap.VertexStride = 12;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bd.ByteWidth = sizeof(ConstantBufferMatrix);
		bd.MiscFlags = 0;
		ID3D11Buffer* buff_;
		checkResult(_device->CreateBuffer(&bd, NULL, &buff_), "Creation of constant buffer for ViewProj failed");
		_textureMap.Buffer.push_back(buff_);
		_textureMap.Buffer.push_back(buff_);
		_textureMap.IndexOfBuffer.push_back(1);
		
		ID3D11Buffer* buff2_;
		checkResult(_device->CreateBuffer(&bd, NULL, &buff2_), "Creation of constant buffer for ViewProj failed");
		_colorMap.Buffer.push_back(buff2_);
		_colorMap.IndexOfBuffer.push_back(1);
		bd.ByteWidth = sizeof(float4);

		ID3D11Buffer* buff3_;
		checkResult(_device->CreateBuffer(&bd, NULL, &buff3_), "Creation of constant buffer for ViewProj failed");
		_colorMap.Buffer.push_back(buff3_);
		_colorMap.IndexOfBuffer.push_back(2);

		safeRelease(BlobVS_);
		safeRelease(BlobPS_);

		return true;
	}
	void D3dRender::_createSystemBox()
	{
		Vertex::System* verts_ = new Vertex::System[8];
		verts_[0] = Vertex::System(float3(0.0f, 0.0f, 0.0f)); verts_[1] = Vertex::System(float3(0.0f, 1.0f, 0.0f));
		verts_[2] = Vertex::System(float3(1.0f, 1.0f, 0.0f)); verts_[3] = Vertex::System(float3(1.0f, 0.0f, 0.0f));
		verts_[4] = Vertex::System(float3(0.0f, 0.0f, 1.0f)); verts_[5] = Vertex::System(float3(0.0f, 1.0f, 1.0f));
		verts_[6] = Vertex::System(float3(1.0f, 1.0f, 1.0f)); verts_[7] = Vertex::System(float3(1.0f, 0.0f, 1.0f));

		unsigned int* inds_ = new unsigned int[16];
		inds_[0] = 0; inds_[1] = 1; inds_[2] = 2; inds_[3] = 3;
		inds_[4] = 0; inds_[5] = 4; inds_[6] = 7; inds_[7] = 3;
		inds_[8] = 2; inds_[9] = 6; inds_[10] = 7; inds_[11] = 6;
		inds_[12] = 5; inds_[13] = 4; inds_[14] = 5; inds_[15] = 1;


		D3D11_BUFFER_DESC bd_;
		ZeroMemory(&bd_, sizeof(bd_));
		bd_.Usage = D3D11_USAGE_DEFAULT;
		bd_.ByteWidth = sizeof(Vertex::System) * 8;
		bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA initData_;
		ZeroMemory(&initData_, sizeof(initData_));
		initData_.pSysMem = verts_;

		SystemModel* mdl_ = new SystemModel();
		
		ID3D11Buffer* vBuf_;
		createBuffer(&bd_, &initData_, &vBuf_);

		ZeroMemory(&bd_, sizeof(bd_));
		bd_.Usage = D3D11_USAGE_DEFAULT;
		bd_.ByteWidth = sizeof(UINT)* 16;
		bd_.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd_.CPUAccessFlags = 0;
		bd_.MiscFlags = 0;
		ZeroMemory(&initData_, sizeof(initData_));
		initData_.pSysMem = inds_;

		ID3D11Buffer* iBuf_;
		createBuffer(&bd_, &initData_, &iBuf_);
		mdl_->setBuffers(vBuf_, iBuf_, 16);

		_models[AMT_COLORMAP].push_back(mdl_);
		vector<XMFLOAT4X4*> list_;
		_worldMatrixs[AMT_COLORMAP].push_back(list_);
		delete verts_;			//NEED?
		delete inds_;
	}
#pragma endregion

#pragma region renderFunctions
	void D3dRender::render()
	{
		_beginScene();

		_immediateContext->RSSetState(_rs.Solid);

		_immediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
		_prepareToRenderTechnique(_colorMap);
		if(_renderTerrainQuadTree)
			_renderColorMapModel(_models[AMT_COLORMAP][SMT_QUADTREE], &_worldMatrixs[AMT_COLORMAP][SMT_QUADTREE]);

		_immediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		_prepareToRenderTechnique(_textureMap);
		for(unsigned int i = 0; i < _models[AMT_TEXTUREMAP].size(); i++)
			_renderTextureMapModel(_models[AMT_TEXTUREMAP][i], &_worldMatrixs[AMT_TEXTUREMAP][i]);

		if(_renderTerrainWireframe)
			_immediateContext->RSSetState(_rs.Wireframe);
		_prepareToRenderTechnique(_terrainTech);
		_immediateContext->IASetIndexBuffer(_terrainTileIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		for(unsigned int i = 0; i < _terrainTiles.size(); i++)
			_renderTerrainTile(_terrainTiles[i]);

		_endScene();
	}
	void D3dRender::_renderTerrainTile(Model* model)
	{
		UINT offset_ = 0;
		_immediateContext->PSSetShaderResources(0, 1, model->getTexture());
		_immediateContext->IASetVertexBuffers(0, 1, model->getVertexBuffer(), &_terrainTech.VertexStride, &offset_);
		_immediateContext->DrawIndexed(model->getIndexCount(), 0, 0);
	}
	void D3dRender::_renderColorMapModel(ModelEx* model, vector<XMFLOAT4X4*>* matrixs)
	{
		UINT offset_ = 0;
		_immediateContext->IASetVertexBuffers(0, 1, model->getVertexBuffer(), &_colorMap.VertexStride, &offset_);
		_immediateContext->IASetIndexBuffer(model->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

		for(unsigned int j = 0; j < matrixs->size(); j++)
		{
			_mapConstantBufferResource(&_colorMap.Buffer[0], matrixs[0][j]);
			_immediateContext->VSSetConstantBuffers(_colorMap.IndexOfBuffer[0], 1, &_colorMap.Buffer[0]);
			_mapConstantBufferResource(&_colorMap.Buffer[1], model->getColor());
			_immediateContext->PSSetConstantBuffers(_colorMap.IndexOfBuffer[1], 1, &_colorMap.Buffer[1]);
			_immediateContext->DrawIndexed(model->getIndexCount(), 0, 0);
		}
	}
	void D3dRender::_renderTextureMapModel(ModelEx* model, vector<XMFLOAT4X4*>* matrixs)
	{
		UINT offset_ = 0;
		_immediateContext->PSSetShaderResources(0, 1, model->getTexture());
		_immediateContext->IASetVertexBuffers(0, 1, model->getVertexBuffer(), &_textureMap.VertexStride, &offset_);
		_immediateContext->IASetIndexBuffer(model->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

		for(unsigned int j = 0; j < matrixs->size(); j++)
		{
			_mapConstantBufferResource(&_textureMap.Buffer[0], matrixs[0][j]);
			_immediateContext->VSSetConstantBuffers(_textureMap.IndexOfBuffer[0], 1, &_textureMap.Buffer[0]);
			_immediateContext->DrawIndexed(model->getIndexCount(), 0, 0);
		}
	}
	void D3dRender::_prepareToRenderTechnique(TechniqueVP tech)
	{
		_immediateContext->VSSetShader(tech.VS, nullptr, 0);
		_immediateContext->PSSetShader(tech.PS, nullptr, 0);
		_immediateContext->IASetInputLayout(tech.IL);
	}
	void D3dRender::_beginScene()
	{
		_immediateContext->ClearRenderTargetView(_renderTargetView, _sceneColor);
		_immediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
		_mapViewProjectionBufferResource();
	}
	void D3dRender::_endScene()
	{
		_swapChain->Present(1, 0);
	}
#pragma endregion

#pragma region additionalFunctions
	void D3dRender::setVisibleTerrainQuadTree(bool set)
	{
		_renderTerrainQuadTree = set;
	}
	void D3dRender::setTerrainWireframe(bool set)
	{
		_renderTerrainWireframe = set;
	}
	precomputeRay* D3dRender::getPickingRay(int x, int y)
	{
		XMFLOAT2 v_;
		v_.x = (((2.0f * x) / _sizeX) - 1) / _perspectiveMatrix._11;
		v_.y = -(((2.0f * y) / _sizeY) - 1) / _perspectiveMatrix._22;

		XMFLOAT4X4 mInv_;
		XMVECTOR nullVec_;XMFLOAT3 pickDir;

		XMStoreFloat4x4(&mInv_, XMMatrixInverse(&nullVec_, XMLoadFloat4x4(Camera::getInstance().getViewMatrixPointer())));

		pickDir.x = v_.x * mInv_._11 + v_.y * mInv_._21 + mInv_._31;
		pickDir.y = v_.x * mInv_._12 + v_.y * mInv_._22 + mInv_._32;
		pickDir.z = v_.x * mInv_._13 + v_.y * mInv_._23 + mInv_._33;

		XMStoreFloat3(&pickDir, XMVector3Normalize(XMLoadFloat3(&pickDir)));
		precomputeRay* r = new precomputeRay();
		r->makeRay(Camera::getInstance().getPositionPointer()[0], pickDir);
		return r;
	}
	void D3dRender::setRasterizerState(int stateType)
	{
		switch(stateType)
		{
		case 0:
			_immediateContext->RSSetState(_rs.Solid);
			break;
		case 1:
			_immediateContext->RSSetState(_rs.Wireframe);
			break;
		default:		break;
		}
	}
	bool D3dRender::resizeBuffer(int sizeX, int sizeY)
	{
		_sizeX = sizeX; _sizeY = sizeY;
		_immediateContext->ClearState();
		_immediateContext->OMSetRenderTargets(0, NULL, NULL);

		_depthStencil->Release();
		_depthStencilView->Release();
		_renderTargetView->Release();
		_backBuffer->Release();

		checkResult(_swapChain->ResizeBuffers(1, sizeX, sizeY, DXGI_FORMAT_UNKNOWN, 0),"ResizeBuffersError");
		checkResult(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer), "Getting backbuffer of swapChain failed");
		checkResult(_device->CreateRenderTargetView(_backBuffer, NULL, &_renderTargetView), "Creation of RenderTargetView failed");

		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory(&descDepth, sizeof(descDepth));
		descDepth.Width = _sizeX;	descDepth.Height = _sizeY;
		descDepth.MipLevels = 1;	descDepth.ArraySize = 1;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1;	descDepth.SampleDesc.Quality = 0;
		descDepth.Usage = D3D11_USAGE_DEFAULT;	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags = 0;	descDepth.MiscFlags = 0;
		checkResult(_device->CreateTexture2D(&descDepth, NULL, &_depthStencil), "Creation of depth stencil texture failed");
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));	descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;	descDSV.Texture2D.MipSlice = 0;
		checkResult(_device->CreateDepthStencilView(_depthStencil, &descDSV, &_depthStencilView), "Creation of depth stencil view failed");
	
		D3D11_VIEWPORT vp;	vp.Width = (FLOAT)_sizeX;	vp.Height = (FLOAT)_sizeY;	vp.MinDepth = 0.0f;	vp.MaxDepth = 1.0f;	vp.TopLeftX = 0;	vp.TopLeftY = 0;
		_immediateContext->RSSetViewports(1, &vp);

		_immediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

		_PerspectiveMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)_sizeX / (FLOAT)_sizeY, _config.Znear, _config.Zfar);
		_OrthograficMatrix = XMMatrixOrthographicLH((FLOAT)_sizeX, (FLOAT)_sizeY, -_config.Zfar, _config.Zfar);
		XMStoreFloat4x4(&_perspectiveMatrix, _PerspectiveMatrix);

		return true;
	}
	bool D3dRender::needToInitializeModel(string fileName, int* indexTechnique, int* index)
	{
		for(unsigned int i = 0; i < _models.size(); i++)
			for(unsigned int j = 0; j < _models[i].size(); j++)
				if(!strcmp(fileName.c_str(),  _models[i][j]->getFileName()))
				{
					indexTechnique[0] = i;
					index[0] = j;
					return false;
				}
		return true;
	}
	XMFLOAT4X4* D3dRender::addModelMatrix(int indexTechnique, int index)
	{
		XMFLOAT4X4* worldMatrix_ = new XMFLOAT4X4();
		XMStoreFloat4x4(worldMatrix_, XMMatrixIdentity());
		_worldMatrixs[indexTechnique][index].push_back(worldMatrix_);
		return _worldMatrixs[indexTechnique][index][_worldMatrixs[indexTechnique][index].size() - 1];
	}
	void D3dRender::_mapViewProjectionBufferResource()
	{
		XMMATRIX viewProjection_ = XMMatrixMultiply(XMLoadFloat4x4(Camera::getInstance().getViewMatrixPointer()), _PerspectiveMatrix);
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		_immediateContext->Map(_bViewProj, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		auto pData = reinterpret_cast<ConstantBufferMatrix*>(MappedResource.pData);
		XMStoreFloat4x4(&pData->matr, viewProjection_);
		_immediateContext->Unmap(_bViewProj, 0);

		_immediateContext->VSSetConstantBuffers(0, 1, &_bViewProj);
	//	_immediateContext->GSSetConstantBuffers(0, 1, &_bViewProj);
	//	_immediateContext->CSSetConstantBuffers(0, 1, &_bViewProj);
	//	_immediateContext->PSSetConstantBuffers(0, 1, &_bViewProj);
	//	_immediateContext->HSSetConstantBuffers(0, 1, &_bViewProj);
	//	_immediateContext->DSSetConstantBuffers(0, 1, &_bViewProj);
	}
	void D3dRender::_mapConstantBufferResource(ID3D11Buffer** buffer, XMFLOAT4* vector)
	{
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		HRESULT hr = _immediateContext->Map(buffer[0], 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		auto pData = reinterpret_cast<XMFLOAT4*>(MappedResource.pData);
		XMStoreFloat4(&pData[0], XMLoadFloat4(vector));
		_immediateContext->Unmap(buffer[0], 0);
	}
	void D3dRender::_mapConstantBufferResource(ID3D11Buffer** buffer, XMFLOAT4X4* matrix)
	{
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		HRESULT hr = _immediateContext->Map(buffer[0], 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		auto pData = reinterpret_cast<ConstantBufferMatrix*>(MappedResource.pData);
		XMStoreFloat4x4(&pData->matr, XMLoadFloat4x4(matrix));
		_immediateContext->Unmap(buffer[0], 0);
	}
	void D3dRender::mapResource(ID3D11Buffer* buf, D3D11_MAPPED_SUBRESOURCE* mappedSubResource, D3D11_MAP mapType)
	{
		HRESULT hr = _immediateContext->Map(buf, 0, mapType, 0, mappedSubResource);
	}
	void D3dRender::unmapResource(ID3D11Buffer* buf)
	{
		_immediateContext->Unmap(buf, 0);
	}
	bool D3dRender::_compileShaderFromFile(LPCSTR szFileName, const D3D_SHADER_MACRO* pDefines,
		LPCSTR szEntryPoint, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob** ppBlobOut)
	{
		HRESULT hr; ID3DBlob* pErrorBlob;
		hr = D3DX11CompileFromFile(szFileName, pDefines, NULL, szEntryPoint, 
			pTarget, Flags1, Flags2, NULL, ppBlobOut, &pErrorBlob, NULL);
		if(FAILED(hr))
		{
			if(pErrorBlob != NULL)
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
			ErrorMessage = reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
			if(pErrorBlob) pErrorBlob->Release();
			return false;
		}
		if(pErrorBlob) pErrorBlob->Release();

		return true;
	}
	bool D3dRender::createBuffer(D3D11_BUFFER_DESC* bd, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buff)
	{
		ID3D11Buffer* buf_;
		checkResult(_device->CreateBuffer(bd, data, &buf_), "CreateBuffer failed");
		buff[0] = buf_;
		return true;
	}
	XMFLOAT4X4* D3dRender::addTextureModel(TextureModel* model)
	{
		vector<XMFLOAT4X4*> list_;
		_worldMatrixs[AMT_TEXTUREMAP].push_back(list_);
		_models[AMT_TEXTUREMAP].push_back(model);
		return addModelMatrix(AMT_TEXTUREMAP, 0);
	}
	bool D3dRender::createTexture(string fileName, ID3D11ShaderResourceView** texture)
	{
		D3DX11_IMAGE_LOAD_INFO ILI;
		HRESULT hr;
		D3DX11CreateShaderResourceViewFromFile(_device, fileName.c_str(), NULL, NULL, &texture[0], &hr);
		return true;
	}
	bool D3dRender::createTexture(string fileName, D3DX11_IMAGE_LOAD_INFO* ili, ID3D11ShaderResourceView** texture)
	{
		HRESULT hr;
		D3DX11CreateShaderResourceViewFromFile(_device, fileName.c_str(), ili, NULL, &texture[0], &hr);
		return true;
	}
#pragma endregion

#pragma region interface for terrain
void D3dRender::clearQuadTreeMatrixVector()
{
	_worldMatrixs[AMT_COLORMAP][SMT_QUADTREE].clear();
}
void D3dRender::addQuadTreeModel(float3* max, float3* center)
{
	XMFLOAT4X4* worldMatrix_ = new XMFLOAT4X4();
	XMStoreFloat4x4(worldMatrix_, (XMMatrixMultiply(XMMatrixScaling(max->x, max->y, max->z), XMMatrixTranslation(center->x, center->y, center->z))));
	_worldMatrixs[AMT_COLORMAP][SMT_QUADTREE].push_back(worldMatrix_);
}
void D3dRender::saveResourceToFile(string fileName, ID3D11Resource* resource)
{
	D3DX11SaveTextureToFile(_immediateContext, resource, D3DX11_IMAGE_FILE_FORMAT::D3DX11_IFF_DDS, fileName.c_str());
}
void D3dRender::setTerrainModels(ID3D11Buffer** vertexBuffers, ID3D11ShaderResourceView** textures, int count, ID3D11Buffer* indexBuffer, int indexCount)
{
	for(unsigned int j = 0; j < _terrainTiles.size(); j++)	{	_terrainTiles[j]->shutdown();	delete _terrainTiles[j]; }
	_terrainTiles.clear();

	for(int i = 0; i < count; i++)
	{
		Model* mdl = new Model();
		mdl->setBuffers(vertexBuffers[i], NULL, indexCount);
		mdl->setTexture(textures[i]);
		_terrainTiles.push_back(mdl);
	}

	_terrainTileIndexBuffer = indexBuffer;
}
#pragma endregion
