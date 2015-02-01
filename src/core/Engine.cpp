#include "Engine.h"

Engine::Engine()
{
	_cameraMangerType = CMT_REDACTORFREE;
	ErrorMessage = "Engine";
	_active = true;
	_d3dRender = 0;
	_scene = 0;
	_camera = 0;
	_inputManager = 0;
}
void Engine::cameraManagerSwitch()
{
	switch(_cameraMangerType)
	{
	case CMT_REDACTOR:
		_cameraManager = _redactorCameraManager;
		break;
	case CMT_REDACTORFREE:
		_cameraManager = _redactorFreeCameraManager;
		break;
	}
}
bool Engine::initialize(HWND* hwnd, int sizeX, int sizeY)
{
	_d3dRender = &D3dRender::getInstance();
	_d3dRender->setInitialize(hwnd[0], sizeX, sizeY);
	safeSystemInit(_d3dRender);
	_scene = &Scene::getInstance();
	safeSystemInit(_scene);
	_parser = &Parser::getInstance();

	_inputManager = &InputManager::getInstance();
	_inputManager->setInitialize(hwnd[0]);
	safeSystemInit(_inputManager);

	_camera = new Camera();

#pragma region Camera manager init
	//Create redactor now & use RedactorCameraManager;
	_redactorFreeCameraManager = new RedactorFreeCameraManager();
	_redactorFreeCameraManager->initialize(_camera);
	_redactorFreeCameraManager->setInputInterface(_inputManager);

	_redactorCameraManager = new RedactorCameraManager();
	_redactorCameraManager->initialize(_camera);
	_redactorCameraManager->setInputInterface(_inputManager);

	cameraManagerSwitch();
#pragma endregion

	_d3dRender->ViewMatrix = _camera->getViewMatrixPointer();

	return true;
}
void Engine::shutdown()
{
	safeShutdown(_d3dRender);
	safeShutdown(_scene);
	safeShutdown(_camera);
}
void Engine::setActive(bool value)
{
	_active = value;
	if(_active && _inputManager) _inputManager->acquire();
}
void Engine::run()
{
	createMapFromFile("resources/aml/rock_1.aml");
	MSG msg_;
	bool done_ = false;
	while(!done_)
	{
		if(PeekMessage(&msg_, NULL, 0, 0, PM_REMOVE))
		{
			if(msg_.message == WM_QUIT)
			{
				done_ = true;
			}
			// may be need to update direct input not every frame
			/*else if(msg_.message == WM_KEYDOWN)
			{
			}
			else if(msg_.message == WM_KEYUP)
			{
			}*/
			else
			{
				TranslateMessage(&msg_);
				DispatchMessage(&msg_);
			}
		}
		else
		{
			if(_active)
			{
				// need to think about this function!
				/*if(_keys[VK_ESCAPE])
				done_ = true;
				else*/
				{
					safeUpdate(_inputManager);
					//_scene->update();
					_cameraManager->update();
					//_camera->update();
					_d3dRender->render();
				}
			}
		}
	}
}
void Engine::setCameraManagerType(CameraManagerType cameraType)
{
	_cameraMangerType = cameraType;
	cameraManagerSwitch();
}
bool Engine::createMapFromFile(string fileName)
{
	//tryOpenStream(fileName);
	createModelFromFile(fileName);
	//tryCloseStream();
	return true;
}
bool Engine::createModelFromFile(string fileName)
{
	tryOpenStream(fileName);

	int numV_ = 0;  int numF_ = 0; int numTV_ = 0;
	tryReadInt(&numV_); tryReadInt(&numF_); tryReadInt(&numTV_);
	vector<XMFLOAT3> verts_;		vector<XMFLOAT2> tVerts_;		vector<XMFLOAT3> norms_;
	vector<XMINT3> vertFaces;		vector<XMINT3> tVertFaces;

	for(int i = 0; i < numV_; i++)
	{
		XMFLOAT3 float3_;
		tryReadFloat(&float3_.x); tryReadFloat(&float3_.y); tryReadFloat(&float3_.z);
		verts_.push_back(float3_);
		tryReadFloat(&float3_.x); tryReadFloat(&float3_.y); tryReadFloat(&float3_.z);
		norms_.push_back(float3_);
	}
	for(int i = 0; i < numTV_; i++)
	{
		XMFLOAT2 float2_; float left_;
		tryReadFloat(&float2_.x); tryReadFloat(&float2_.y); tryReadFloat(&left_);
		tVerts_.push_back(float2_);
	}
	for(int i = 0; i < numF_; i++)
	{
		XMINT3 int3_;
		tryReadInt(&int3_.x);	tryReadInt(&int3_.y);	tryReadInt(&int3_.z);
		vertFaces.push_back(int3_);
		tryReadInt(&int3_.x); tryReadInt(&int3_.y); tryReadInt(&int3_.z);
		tVertFaces.push_back(int3_);
	}
	vector<Vertex::Simple> simpleVerts_;
	vector<Vertex::Simple> optimizedVerts_;
	unsigned int countInds_ = 0;
	for(int i = 0; i < numF_; i++)
	{
		simpleVerts_.push_back(Vertex::Simple(verts_[vertFaces[i].x], tVerts_[tVertFaces[i].x], norms_[vertFaces[i].x]));
		simpleVerts_.push_back(Vertex::Simple(verts_[vertFaces[i].y], tVerts_[tVertFaces[i].y], norms_[vertFaces[i].y]));
		simpleVerts_.push_back(Vertex::Simple(verts_[vertFaces[i].z], tVerts_[tVertFaces[i].z], norms_[vertFaces[i].z]));
	}
	countInds_ = simpleVerts_.size();
	verts_.clear();	tVerts_.clear();	norms_.clear();	vertFaces.clear();	tVertFaces.clear();
	unsigned int* indsForIndexBuffer = new unsigned int[countInds_];

	for(unsigned int i = 0; i < countInds_; i++) indsForIndexBuffer[i] = i;
	bool write = true;
	optimizedVerts_.push_back(simpleVerts_[0]);
	for(unsigned int i = 1; i < countInds_; i++)
	{
		write = true;
		for(unsigned int j = 0; j < optimizedVerts_.size(); j++)
		{
			if(simpleVerts_[i].position.x == optimizedVerts_[j].position.x && simpleVerts_[i].texCoord.x == optimizedVerts_[j].texCoord.x &&
				simpleVerts_[i].position.y == optimizedVerts_[j].position.y && simpleVerts_[i].texCoord.y == optimizedVerts_[j].texCoord.y &&
				simpleVerts_[i].position.z == optimizedVerts_[j].position.z)
			{
				write = false;
				indsForIndexBuffer[i] = j;
			}
		}
		if(write)
		{
			optimizedVerts_.push_back(simpleVerts_[i]);
			indsForIndexBuffer[i] = optimizedVerts_.size() - 1;
		}
	}

	Vertex::Simple* vertsForBuffer = new Vertex::Simple[optimizedVerts_.size()];
	for(unsigned int i = 0; i < optimizedVerts_.size(); i++) vertsForBuffer[i] = optimizedVerts_[i];

	tryCloseStream();
	
	D3D11_BUFFER_DESC bd_;
	ZeroMemory(&bd_, sizeof(bd_));
	bd_.Usage = D3D11_USAGE_DEFAULT;
	bd_.ByteWidth = sizeof(Vertex::Simple) * optimizedVerts_.size();
	bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA initData_;
	ZeroMemory(&initData_, sizeof(initData_));
	initData_.pSysMem = vertsForBuffer;

	ID3D11Buffer* vBuf_;
	checkRenderResult(_d3dRender->createBuffer(&bd_, &initData_, &vBuf_));

	ZeroMemory(&bd_, sizeof(bd_));
	bd_.Usage = D3D11_USAGE_DEFAULT;
	bd_.ByteWidth = sizeof(UINT)* countInds_;
	bd_.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_.CPUAccessFlags = 0;
	bd_.MiscFlags = 0;
	ZeroMemory(&initData_, sizeof(initData_));
	initData_.pSysMem = indsForIndexBuffer;

	ID3D11Buffer* iBuf_;
	checkRenderResult(_d3dRender->createBuffer(&bd_, &initData_, &iBuf_));

	ID3D11ShaderResourceView* texture_;
	checkRenderResult(_d3dRender->createTexture(fileName.substr(0, fileName.length() - 3) + "dds", &texture_));

	TextureModel* mdl = new TextureModel();
	mdl->setBuffers(vBuf_, iBuf_, countInds_);
	mdl->setTexture(texture_);
	//mdl->WorldMatrix;		FOR ENTITY
	_d3dRender->addTextureModel(mdl);
	return true;
}
