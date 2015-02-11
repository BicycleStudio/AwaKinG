#include "Engine.h"

#pragma region Engine
	Engine::Engine()
	{
		_systemInitialized = false;
		_shortPaths = true;
		_cameraMangerType = CMT_REDACTORFREE;
		ErrorMessage = "Engine";
		_active = true;
		_terrainManager = new TerrainManager();
	}
	RedactorEngine::RedactorEngine()
	{
		_systemInitialized = false;
		_shortPaths = false;
		_cameraMangerType = CMT_REDACTOR;
		ErrorMessage = "RedactorEngine";
		_active = true;
		_redactorTerrainManager = new RedactorTerrainManager();
	}
	bool Engine::initialize(HWND mainHwnd, HWND renderHwnd, int sizeX, int sizeY)
	{
		string path_ = "../../fx/";
		if(!_shortPaths) path_ = "../../" + path_;
		D3dRender::getInstance().setInitialize(renderHwnd, sizeX, sizeY, path_);
	
		safeSystemInit(D3dRender::getInstance());
		safeSystemInit(Scene::getInstance());

		InputManager::getInstance().setInitialize(mainHwnd);
		safeSystemInit(InputManager::getInstance());

	#pragma region Camera manager init
		//Create redactor now & use RedactorCameraManager;
		_redactorFreeCameraManager = new RedactorFreeCameraManager();
		_redactorFreeCameraManager->initialize(&Camera::getInstance());
		_redactorFreeCameraManager->setInputInterface();

		_redactorCameraManager = new RedactorCameraManager();
		_redactorCameraManager->initialize(&Camera::getInstance());
		_redactorCameraManager->setInputInterface();
		
		_cameraManagerSwitch();
	#pragma endregion
	
		_systemInitialized = true;
		return true;
	}
	bool RedactorEngine::initialize(HWND mainHwnd, HWND renderHwnd, int sizeX, int sizeY)
	{
		string path_ = "../../fx/";
		if(!_shortPaths) path_ = "../../" + path_;
		D3dRender::getInstance().setInitialize(renderHwnd, sizeX, sizeY, path_);

		safeSystemInit(D3dRender::getInstance());
		safeSystemInit(Scene::getInstance());

		InputManager::getInstance().setInitialize(mainHwnd);
		safeSystemInit(InputManager::getInstance());

#pragma region Camera manager init
		//Create redactor now & use RedactorCameraManager;
		_redactorFreeCameraManager = new RedactorFreeCameraManager();
		_redactorFreeCameraManager->initialize(&Camera::getInstance());
		_redactorFreeCameraManager->setInputInterface();

		_redactorCameraManager = new RedactorCameraManager();
		_redactorCameraManager->initialize(&Camera::getInstance());
		_redactorCameraManager->setInputInterface();

		_cameraManagerSwitch();
#pragma endregion

		_systemInitialized = true;
		_redactorTerrainManager->initialize();
		return true;
	}
	bool Engine::update()
	{
		safeUpdate(InputManager::getInstance());
		Scene::getInstance().update();
		_cameraManager->update();
		D3dRender::getInstance().render();
		return false;
	}
	void Engine::shutdown()
	{
		D3dRender::getInstance().shutdown();
		delete _terrainManager;
		Scene::getInstance().shutdown();
		Camera::getInstance().shutdown();
	}
	void RedactorEngine::shutdown()
	{
		D3dRender::getInstance().shutdown();
		delete _redactorTerrainManager;
		Scene::getInstance().shutdown();
		Camera::getInstance().shutdown();
	}
	bool Engine::resizeRenderBuffer(int sizeX, int sizeY)
	{
		return D3dRender::getInstance().resizeBuffer(sizeX, sizeY);
	}
	void Engine::setActive(bool value)
	{
		_active = value;
		if(_active && _systemInitialized) InputManager::getInstance().acquire();
	}
	bool Engine::active()
	{
		return _active;
	}
	void Engine::setCameraManagerType(CameraManagerType cameraType)
	{
		_cameraMangerType = cameraType;
		_cameraManagerSwitch();
	}
	void Engine::_cameraManagerSwitch()
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
	bool Engine::_createEntity(Entity** entity, string fileName)
	{
		int modelIndex_ = 0;	int techniqueIndex_ = 0;
		if(!D3dRender::getInstance().needToInitializeModel(fileName, &techniqueIndex_, &modelIndex_))
		{
			entity[0] = new Entity();
			entity[0]->initialize(D3dRender::getInstance().addModelMatrix(techniqueIndex_, modelIndex_));
			return true;
		}
		tryOpenStream(fileName, "r");

		int numV_ = 0;  int numF_ = 0; int numTV_ = 0;
		tryReadInt(&numV_); tryReadInt(&numF_); tryReadInt(&numTV_);
		vector<XMFLOAT3> verts_;		vector<XMFLOAT2> tVerts_;		vector<XMFLOAT3> norms_;
		vector<int3> vertFaces;		vector<int3> tVertFaces;

		for(int i = 0; i < numV_; i++)
		{
			XMFLOAT3 float3_;
			tryReadFloat(&float3_.x); tryReadFloat(&float3_.z); tryReadFloat(&float3_.y);
			verts_.push_back(float3_);
			tryReadFloat(&float3_.x); tryReadFloat(&float3_.z); tryReadFloat(&float3_.y);
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
			int3 int3_;
			tryReadInt(&int3_.x);	tryReadInt(&int3_.z);	tryReadInt(&int3_.y);
			vertFaces.push_back(int3_);
			tryReadInt(&int3_.x); tryReadInt(&int3_.z); tryReadInt(&int3_.y);
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
		checkRenderResult(D3dRender::getInstance().createBuffer(&bd_, &initData_, &vBuf_));

		ZeroMemory(&bd_, sizeof(bd_));
		bd_.Usage = D3D11_USAGE_DEFAULT;
		bd_.ByteWidth = sizeof(UINT)* countInds_;
		bd_.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd_.CPUAccessFlags = 0;
		bd_.MiscFlags = 0;
		ZeroMemory(&initData_, sizeof(initData_));
		initData_.pSysMem = indsForIndexBuffer;

		ID3D11Buffer* iBuf_;
		checkRenderResult(D3dRender::getInstance().createBuffer(&bd_, &initData_, &iBuf_));

		ID3D11ShaderResourceView* texture_;
		checkRenderResult(D3dRender::getInstance().createTexture(fileName.substr(0, fileName.length() - 3) + "dds", &texture_));

		TextureModel* mdl = new TextureModel();
		mdl->setBuffers(vBuf_, iBuf_, countInds_);
		mdl->setTexture(texture_);
		mdl->setFileName(fileName);

		entity[0] = new Entity();
		entity[0]->initialize(D3dRender::getInstance().addTextureModel(mdl));

		return true;
	}
	void Engine::loadTerrain(string fileName)
	{
		_terrainManager->loadFromFile(fileName);
	}
#pragma endregion

#pragma region Redactor
	#pragma region Terrain
		void RedactorEngine::diamondSquareTerrain()
		{ 
			_redactorTerrainManager->diamondSquareAlgorythm();
		}
		bool RedactorEngine::createTerrain(int gridX, int gridY)
		{
			return _redactorTerrainManager->generate(gridX, gridY);
		}
		void RedactorEngine::loadTerrain(string fileName)
		{
			_redactorTerrainManager->loadFromFile(fileName);
		}
		void RedactorEngine::randomizeTerrain(int diapazon)
		{
			_redactorTerrainManager->randomize(diapazon);
		}
		void RedactorEngine::blurTerrain(int value)
		{
			_redactorTerrainManager->blurHeightmap(value);
		}
		void RedactorEngine::saveTerrain(string fileName)
		{
			_redactorTerrainManager->saveToFile(fileName);
		}
		void RedactorEngine::setTerrainQuadTreeVisible(bool set)
		{
			D3dRender::getInstance().setVisibleTerrainQuadTree(set);
		}
		void RedactorEngine::setTerrainWireframe(bool set)
		{
			D3dRender::getInstance().setTerrainWireframe(set);
		}
		void RedactorEngine::terrainTerraformShow(int posX, int posY)
		{
			precomputeRay* precomputeRay_ = D3dRender::getInstance().getPickingRay(posX, posY);
			_redactorTerrainManager->terraformShow(precomputeRay_);
		}
		void RedactorEngine::terrainTerraformApply(int posX, int posY)
		{
			precomputeRay* precomputeRay_ = D3dRender::getInstance().getPickingRay(posX, posY);
			_redactorTerrainManager->terraformApply(precomputeRay_);
		}
		void RedactorEngine::terrainTerraformApplySmIn(int posX, int posY)
		{
			precomputeRay* precomputeRay_ = D3dRender::getInstance().getPickingRay(posX, posY);
			_redactorTerrainManager->terraformApplySmIn(precomputeRay_);
		}
		void RedactorEngine::terrainTerraformApplySmInOut(int posX, int posY)
		{
			precomputeRay* precomputeRay_ = D3dRender::getInstance().getPickingRay(posX, posY);
			_redactorTerrainManager->terraformApplySmInOut(precomputeRay_);
		}
		void RedactorEngine::terrainTerraformApplySmOut(int posX, int posY)
		{
			precomputeRay* precomputeRay_ = D3dRender::getInstance().getPickingRay(posX, posY);
			_redactorTerrainManager->terraformApplySmOut(precomputeRay_);
		}

		void RedactorEngine::terrainSetTerraPenSize(int in, int out)
		{
			_redactorTerrainManager->setTerraPenSize(in, out);
		}
		void RedactorEngine::terrainSetTerraPenHard(float hard)
		{
			_redactorTerrainManager->setTerraPenHard(hard);
		}
		void RedactorEngine::terrainSetTerraPenSmoothKoeff(float smoothKoeff)
		{
			_redactorTerrainManager->setTerraPenSmoothKoeff(smoothKoeff);
		}
		void RedactorEngine::textureWorkTerrain(int posX, int posY)
		{
			precomputeRay* precomputeRay_ = D3dRender::getInstance().getPickingRay(posX, posY);
			_redactorTerrainManager->textureWork(precomputeRay_);
		}
		void RedactorEngine::setTerrainPenVisible(bool set)
		{
			D3dRender::getInstance().setTerrainPenVisible(set);
		}
	#pragma endregion

	bool RedactorEngine::createMapFromFile(string fileName)
	{
		tryOpenStream(fileName, "r");
		string errorsOpening_;
		int countEntities_ = 0; tryReadInt(&countEntities_);
		for(int i = 0; i < countEntities_; i++)
		{
			Entity* entity_;
			char* mdlFileName = new char[255];
			XMFLOAT3 pos_; XMFLOAT3 scl_; XMFLOAT3 rot_;
			tryReadString(&mdlFileName);
			if(!_createEntity(&entity_, mdlFileName))
			{
				errorsOpening_ += Parser::getInstance().ErrorMessage + "\n";
				tryReadFloat(&pos_.x); tryReadFloat(&pos_.y); tryReadFloat(&pos_.z);
				tryReadFloat(&scl_.x); tryReadFloat(&scl_.y); tryReadFloat(&scl_.z);
				tryReadFloat(&rot_.x); tryReadFloat(&rot_.y); tryReadFloat(&rot_.z);
				continue;
			}
			tryReadFloat(&pos_.x); tryReadFloat(&pos_.y); tryReadFloat(&pos_.z);
			tryReadFloat(&scl_.x); tryReadFloat(&scl_.y); tryReadFloat(&scl_.z);
			tryReadFloat(&rot_.x); tryReadFloat(&rot_.y); tryReadFloat(&rot_.z);

			entity_->setTransformation(pos_, scl_, rot_);
			Scene::getInstance().addEntity(entity_);
		}
		if(errorsOpening_ != "")
			MessageBox(NULL, errorsOpening_.c_str(), "openMapError error", MB_OK | MB_ICONERROR);
		tryCloseStream();
		return true;
	}
	void RedactorEngine::setShortPaths()
	{
		_shortPaths = true;
		string path_ = "../../media/terrain/_2048.dds";
		_redactorTerrainManager->set2048Path(path_);
	}
	void RedactorEngine::setCameraSpeed(float speed)
	{
		_redactorCameraManager->setSpeed(speed);
		_redactorFreeCameraManager->setSpeed(speed);
	}
#pragma endregion

