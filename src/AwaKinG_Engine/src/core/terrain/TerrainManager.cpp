#include "TerrainManager.h"
#pragma region main functions
	void RedactorTerrainManager::initialize()
	{
		_bioms.push_back(Biom(1000.0f, 50.0f)); _bioms.push_back(Biom(10.0f, 100.0f));
		_bioms.push_back(Biom(10.0f, 10.0f));		_bioms.push_back(Biom(-1000.0f, 30.0f));
		_heightPen = new HeightTerrainPen();
		_texturePen = new TextureTerrainPen();
	}
	TerrainManager::TerrainManager()
	{
		_indexBuffer = NULL;
		_2048Path = "../../media/terrain/_2048.dds";
		_quadTree = NULL;
	}
	RedactorTerrainManager::RedactorTerrainManager()
	{
		_indexBuffer = NULL;
		_2048Path = "../../../../media/terrain/_2048.dds";
		_quadTree = NULL;
	}
	void RedactorTerrainManager::shutdown()
	{
		delete _heightPen;
		delete _texturePen;

		safeRelease(_indexBuffer);
		for(int i = 0; i < _props.numTiles; i++)
		{
			safeRelease(_vertexBuffers[i]);
			delete _vertexBuffers[i];
		}
		for(int i = 0; i < _props.numTiles; i++)
		{
			safeRelease(_textures[i]);
			delete _textures[i];
		}
		_props.Release();
		if(_quadTree){ delete _quadTree; _quadTree = NULL; }
	}
	void TerrainManager::shutdown()
	{
		safeRelease(_indexBuffer);
		for(int i = 0; i < _props.numTiles; i++)
		{
			safeRelease(_vertexBuffers[i]);
			delete _vertexBuffers[i];
		}
		for(int i = 0; i < _props.numTiles; i++)
		{
			safeRelease(_textures[i]);
			delete _textures[i];
		}
		_props.Release();
		if(_quadTree){ delete _quadTree; _quadTree = NULL; }
	}
	bool TerrainManager::_generateGeometry()
	{
		D3D11_BUFFER_DESC bd_;
		ZeroMemory(&bd_, sizeof(bd_));
		bd_.Usage = D3D11_USAGE_DYNAMIC;
		bd_.ByteWidth = sizeof(Vertex::Simple) * _props.numTileVerts;
		bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		D3D11_SUBRESOURCE_DATA initData_;

		_vertexBuffers = new ID3D11Buffer*[_props.numTiles];
		float texs = (float)1.0f / (float)_props.numQuad;
		int ter_ind = 0;
		Vertex::Simple* verts = new Vertex::Simple[_props.numTileVerts];
		for(int ter_ind_x = 0; ter_ind_x < _props.sizeX; ter_ind_x++)
		{
			for(int ter_ind_y = 0; ter_ind_y < _props.sizeY; ter_ind_y++)
			{
				int number = 0;
				for(int i = 0; i < _props.numVerts; i++)
				{
					for(int j = 0; j < _props.numVerts; j++)
					{
						verts[number] = Vertex::Simple(_props.heightMap[_props.pickToHeightMap[ter_ind][number]],
							float2(texs * (float)j, texs * (float)i), _props.normalMap[_props.pickToHeightMap[ter_ind][number]]);
						number++;
					}
				}
				ZeroMemory(&initData_, sizeof(initData_));
				initData_.pSysMem = verts;
				if(!D3dRender::getInstance().createBuffer(&bd_, &initData_, &_vertexBuffers[ter_ind])) { ErrorMessage = "Creation of vertex buffer for terrain"; return false; }
				ter_ind++;
			}
		}
		_createIndexBuffer();

		int dispRawGlob_ = 0;
		for(int i = 0; i < _props.numSectors; i++)
		{
			_props.sectors.push_back(new TerrainSector());
			int startVert_ = _props.numSQuads*((i / _props.sizeSectorX)*_props.numVertsInRaw+  (i % _props.sizeSectorX));

			int savedI_ = 0; int savedJ_ = 0; int savedK_ = 0; int savedL_ = 0; int savedM_ = 0; int savedN_ = 0;
			for(int j = 0; j < _props.numSectorVerts; j++)
			{
				int dispVert_ = (j / _props.numSVerts)*_props.numVertsInRaw + j % _props.numSVerts;
				int check_ = startVert_ + dispVert_;

				_props.sectorsToHeightMap[i][j] = check_;

				switch(_props.heightMapToSectors[check_][0])
				{
				case 0:
					_props.heightMapToSectors[check_] = new int[3];
					_props.heightMapToSectors[check_][0] = 1;
					_props.heightMapToSectors[check_][1] = i;
					_props.heightMapToSectors[check_][2] = j;
					break;
				case 1:
					savedI_ = _props.heightMapToSectors[check_][1];
					savedJ_ = _props.heightMapToSectors[check_][2];

					_props.heightMapToSectors[check_] = new int[5];
					_props.heightMapToSectors[check_][0] = 2;
					_props.heightMapToSectors[check_][1] = savedI_;
					_props.heightMapToSectors[check_][2] = savedJ_;
					_props.heightMapToSectors[check_][3] = i;
					_props.heightMapToSectors[check_][4] = j;
					break;
				case 2:
					savedI_ = _props.heightMapToSectors[check_][1];
					savedJ_ = _props.heightMapToSectors[check_][2];
					savedK_ = _props.heightMapToSectors[check_][3];
					savedL_ = _props.heightMapToSectors[check_][4];

					_props.heightMapToSectors[check_] = new int[7];
					_props.heightMapToSectors[check_][0] = 3;
					_props.heightMapToSectors[check_][1] = savedI_;
					_props.heightMapToSectors[check_][2] = savedJ_;
					_props.heightMapToSectors[check_][3] = savedK_;
					_props.heightMapToSectors[check_][4] = savedL_;
					_props.heightMapToSectors[check_][5] = i;
					_props.heightMapToSectors[check_][6] = j;
					break;
				case 3:
					savedI_ = _props.heightMapToSectors[check_][1];
					savedJ_ = _props.heightMapToSectors[check_][2];
					savedK_ = _props.heightMapToSectors[check_][3];
					savedL_ = _props.heightMapToSectors[check_][4];
					savedM_ = _props.heightMapToSectors[check_][5];
					savedN_ = _props.heightMapToSectors[check_][6];

					_props.heightMapToSectors[check_] = new int[9];
					_props.heightMapToSectors[check_][0] = 4;
					_props.heightMapToSectors[check_][1] = savedI_;
					_props.heightMapToSectors[check_][2] = savedJ_;
					_props.heightMapToSectors[check_][3] = savedK_;
					_props.heightMapToSectors[check_][4] = savedL_;
					_props.heightMapToSectors[check_][5] = savedM_;
					_props.heightMapToSectors[check_][6] = savedN_;
					_props.heightMapToSectors[check_][7] = i;
					_props.heightMapToSectors[check_][8] = j;
					break;
				}
			}
		}
		if(_quadTree)
		{
			vector<QuadTree*>* fathers__ = new vector<QuadTree*>;
			vector<QuadTree*>* fathers2__ = new vector<QuadTree*>;
			fathers__->push_back(_quadTree);
			vector<QuadTree*> childs__;
			childs__.push_back(_quadTree);
			while(!childs__[childs__.size() - 1]->land)
			{
				for(int i = 0; i < fathers__->size(); i++)
				{
					for(int j = 0; j < fathers__[0][i]->childs.size(); j++)
					{
						childs__.push_back(fathers__[0][i]->childs[j]);
						fathers2__->push_back(fathers__[0][i]->childs[j]);
					}
				}
				fathers__ = fathers2__;
				fathers2__ = new vector<QuadTree*>;
			}
			for(int i = childs__.size() - 1; i >=0; i--)
				delete childs__[i];

			fathers__->clear();
			fathers2__->clear();
			childs__.clear();
			delete fathers__;
			delete fathers2__;
		}

		D3dRender::getInstance().clearQuadTreeMatrixVector();
		_quadTree = new QuadTree();

		vector<QuadTree*>* grandChilds_ = new vector<QuadTree*>;
		for(int i = 0; i < _props.numSectors; i++)
		{
			_props.sectors[i]->min = _props.heightMap[_props.sectorsToHeightMap[i][0]];
			_props.sectors[i]->max = _props.heightMap[_props.sectorsToHeightMap[i][_props.numSectorVerts-1]];

			for(int v_id = 0; v_id < _props.numSectorVerts; v_id++)
			{
				if(_props.heightMap[_props.sectorsToHeightMap[i][v_id]].y > _props.sectors[i]->max.y)
					_props.sectors[i]->max.y = _props.heightMap[_props.sectorsToHeightMap[i][v_id]].y;

				if(_props.heightMap[_props.sectorsToHeightMap[i][v_id]].y < _props.sectors[i]->min.y)
					_props.sectors[i]->min.y = _props.heightMap[_props.sectorsToHeightMap[i][v_id]].y;

			}
			_props.sectors[i]->terrainId = _props.heightMapToTerrain[_props.sectorsToHeightMap[i][18]][1];
			_props.sectors[i]->id = i;

			grandChilds_->push_back(new QuadTree(&_props.sectors[i]->max, &_props.sectors[i]->min, i, _props.sectors[i]->terrainId));
			_props.sectors[i]->father = grandChilds_[0][grandChilds_->size() - 1];
		}

		vector<QuadTree*>* childs_ = grandChilds_;
		int rawSize_ = _props.sizeSectorX;
		do
		{
			grandChilds_ = childs_;
			childs_ = new vector<QuadTree*>;
			int counter_ = 0;
			for(int i = 0; i < grandChilds_->size(); i+=2)
			{

				bool right_ = true;
				if(i / rawSize_ != counter_)
				{
					counter_ += 2; i += rawSize_;
					if(i>=grandChilds_->size())  break;
				}
				QuadTree* childTree = new QuadTree();
				childTree->childs.push_back(grandChilds_[0][i]);
				if((i + 1) % (rawSize_))	
					childTree->childs.push_back(grandChilds_[0][i + 1]);	
				else  
					right_ = false; 
				if((i + rawSize_) < grandChilds_->size())
				{
					childTree->childs.push_back(grandChilds_[0][i + rawSize_]);
					if(right_) 
						childTree->childs.push_back(grandChilds_[0][i + rawSize_ + 1]);
					else i--;
				}
				childTree->findMaxMinFromChilds();
				for(int k = 0; k < childTree->childs.size(); k++)
				{
					childTree->childs[k]->father = childTree;
					D3dRender::getInstance().addQuadTreeModel(childTree->childs[k]->worldMatrix);
				}

				childs_->push_back(childTree);
			}
			if(rawSize_ % 2)rawSize_ = rawSize_ / 2 + 1;
			else rawSize_ /= 2;
		} while(childs_->size() > 4);

		for(int i = 0; i < childs_->size(); i++)
		{
			D3dRender::getInstance().addQuadTreeModel(childs_[0][i]->worldMatrix);
			_quadTree->childs.push_back(childs_[0][i]);
			childs_[0][i]->father = _quadTree;
		}
		_quadTree->findMaxMinFromChilds();
		D3dRender::getInstance().addQuadTreeModel(_quadTree->worldMatrix);

		return true;
	}
	bool TerrainManager::_createIndexBuffer()
	{
		_props.indexes = new unsigned int[_props.numIndex];
		unsigned int index = 0;
		for(int i = 0; i < _props.numQuad; i++)
		{
			for(int j = 0; j < _props.numQuad; j++)
			{
				_props.indexes[index] = (unsigned int)(i *  _props.numVerts + j);
				_props.indexes[index + 1] = (unsigned int)(i *  _props.numVerts + j + 1);
				_props.indexes[index + 2] = (unsigned int)((i + 1) *  _props.numVerts + j);

				_props.indexes[index + 3] = (unsigned int)(i *  _props.numVerts + j + 1);
				_props.indexes[index + 4] = (unsigned int)((i + 1) *  _props.numVerts + j + 1);
				_props.indexes[index + 5] = (unsigned int)((i + 1) *  _props.numVerts + j);

				index += 6;
			}
		}
		D3D11_BUFFER_DESC bd_;
		D3D11_SUBRESOURCE_DATA initData_;

		ZeroMemory(&bd_, sizeof(bd_));
		bd_.Usage = D3D11_USAGE_DEFAULT;
		bd_.ByteWidth = sizeof(UINT)* _props.numIndex;
		bd_.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd_.CPUAccessFlags = 0;
		bd_.MiscFlags = 0;
		ZeroMemory(&initData_, sizeof(initData_));
		initData_.pSysMem = _props.indexes;
		if(!D3dRender::getInstance().createBuffer(&bd_, &initData_, &_indexBuffer)) { ErrorMessage = "Creation of index buffer for terrain"; return false; }

	}
	bool TerrainManager::_readVertexBlock(string fileName)
	{
		tryOpenStream(fileName, "r");
		int numV_ = 0; float cellSpace_ = 0.0f; int sizeX_ = 0; int sizeY_ = 0;
		tryReadInt(&numV_); tryReadFloat(&cellSpace_);
		tryReadInt(&sizeX_); tryReadInt(&sizeY_);

		_props.Release();
		_props = Properties(sizeX_, sizeY_);

		for(int ter_i = 0; ter_i < _props.sizeX; ter_i++)
		{
			for(int ter_j = 0; ter_j < _props.sizeY; ter_j++)
			{
				for(int i = 0; i < _props.numVerts; i++)
				{
					for(int j = 0; j < _props.numVerts; j++)
					{
						tryReadFloat(&_props.heightMap[_props.pickToHeightMap[ter_i*_props.sizeX + ter_j][i*_props.numVerts + j]].y);
					}
				}
			}
		}
		tryCloseStream();
		if(!_generateGeometry())		return false;
	}
#pragma endregion
#pragma region virtual functions
	bool TerrainManager::loadFromFile(string fileName)
	{
		_readVertexBlock(fileName);
		_textures = new ID3D11ShaderResourceView*[_props.numTiles];

		string textureFName_ = fileName.substr(0, fileName.length() - 4);
		for(int i = 0; i < _props.numTiles; i++)
		{
			char str[3] = { '_', '_', '_' };
			sprintf_s(str, "%d", i);
			D3dRender::getInstance().createTexture(textureFName_ + str + ".dds", NULL, &_textures[i]);
		}
		D3dRender::getInstance().setTerrainModels(_vertexBuffers, _textures, _props.numTiles, _indexBuffer, _props.numIndex);
		return true;
	}
	bool RedactorTerrainManager::loadFromFile(string fileName)
	{
		_readVertexBlock(fileName);

		delete _countVertToUpdate; delete[] _vertsToUpdate;
		_vertsToUpdate = new int*[_props.numTiles];
		_countVertToUpdate = new int[_props.numTiles];
		for(int i = 0; i<_props.numTiles; i++)
		{
			_countVertToUpdate[i] = 0;
			_vertsToUpdate[i] = new int[100 * 4];
		}

		D3DX11_IMAGE_LOAD_INFO ili_;
		ili_.MipLevels = 1;
		ili_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;// Format.R8G8B8A8_UNorm;
		ili_.Width = 2048;
		ili_.Height = 2048;
		ili_.BindFlags = D3D11_BIND_SHADER_RESOURCE;// BindFlags.ShaderResource;
		ili_.CpuAccessFlags = 0;// CpuAccessFlags.None;
		ili_.MipFilter = D3D11_FILTER_TYPE_LINEAR;
		//ili_.FirstMipLevel = ResourceOptionFlags.None;
		ili_.MiscFlags = 0;
		ili_.Usage = D3D11_USAGE_DEFAULT;//  ResourceUsage.Default;

		_textures = new ID3D11ShaderResourceView*[_props.numTiles];

		string textureFName_ = fileName.substr(0, fileName.length() - 4);
		for(int i = 0; i < _props.numTiles; i++)
		{
			char str[3] = { '_', '_', '_' };
			sprintf_s(str, "%d", i);
			D3dRender::getInstance().createTexture(textureFName_ + str + ".dds", &ili_, &_textures[i]);
		}

		D3dRender::getInstance().setTerrainModels(_vertexBuffers, _textures, _props.numTiles, _indexBuffer, _props.numIndex);

		return true;
	}
#pragma endregion
#pragma region redactor functions
	#pragma region picking
		void RedactorTerrainManager::textureWork(precomputeRay* pickRay)
		{
			vector<QuadTree*> realIntersected_;
			_pick(pickRay, &realIntersected_);

			int terrainId_ = -1;
			float tu; float tv;
			for(int i = 0; i < realIntersected_.size(); i++)
			{
				if(_getQuadIntersectID(_props.sectors[realIntersected_[i]->sectorID], &pickRay->direction, &pickRay->origin, &tu, &tv))
				{
					terrainId_ = realIntersected_[i]->terrainID;
					break;
				}
			}
			if(terrainId_ != -1) _textureWork(terrainId_, float2(tu, tv));
		}
		void RedactorTerrainManager::terraformShow(precomputeRay* pickRay)
		{
			int terrainId_ = -1;
			int quadID = _terraPick(pickRay, &terrainId_);
			if(quadID != -1) _terraformShow(terrainId_, quadID);
			else
			{
				_heightPen->countDrawSizeIn = 0;
				_heightPen->countDrawSizeOut = 0;
			}
		}
		void RedactorTerrainManager::terraformApply(precomputeRay* pickRay)
		{
			int terrainId_ = -1;
			int quadID = _terraPick(pickRay, &terrainId_);
			if(quadID != -1) _terraformApply(terrainId_, quadID);
			else
			{
				_heightPen->countDrawSizeIn = 0;
				_heightPen->countDrawSizeOut = 0;
			}
		}
		void RedactorTerrainManager::terraformApplySmInOut(precomputeRay* pickRay)
		{
			int terrainId_ = -1;
			int quadID = _terraPick(pickRay, &terrainId_);
			if(quadID != -1) _terraformApplySmInOut(terrainId_, quadID);
			else
			{
				_heightPen->countDrawSizeIn = 0;
				_heightPen->countDrawSizeOut = 0;
			}
		}
		void RedactorTerrainManager::terraformApplySmOut(precomputeRay* pickRay)
		{
			int terrainId_ = -1;
			int quadID = _terraPick(pickRay, &terrainId_);
			if(quadID != -1) _terraformApplySmOut(terrainId_, quadID);
			else
			{
				_heightPen->countDrawSizeIn = 0;
				_heightPen->countDrawSizeOut = 0;
			}
		}
		void RedactorTerrainManager::terraformApplySmIn(precomputeRay* pickRay)
		{
			int terrainId_ = -1;
			int quadID = _terraPick(pickRay, &terrainId_);
			if(quadID != -1) _terraformApplySmIn(terrainId_, quadID);
			else
			{
				_heightPen->countDrawSizeIn = 0;
				_heightPen->countDrawSizeOut = 0;
			}
		}
		int RedactorTerrainManager::_terraPick(precomputeRay* pickRay, int* terrainId)
		{
			vector<QuadTree*> realIntersected_;
			_pick(pickRay, &realIntersected_);

			int quadID = -1; int terrainId_ = -1;
			for(int i = 0; i < realIntersected_.size(); i++)
			{
				if(_getQuadIntersectID(_props.sectors[realIntersected_[i]->sectorID], &pickRay->direction, &pickRay->origin, &quadID))
				{
					terrainId_ = realIntersected_[i]->terrainID;
					break;
				}
			}
			terrainId[0] = terrainId_;
			return quadID;
		}
		void RedactorTerrainManager::_pick(precomputeRay* pickRay, vector<QuadTree*>* rayAabbIntersected)
		{
			vector<QuadTree*> intersected_;
			intersected_.push_back(_quadTree);

			QuadTree** trees_ = new QuadTree*[4];
			int count_ = 0; bool done_ = false;

			while(intersected_.size() != 0)
			{
				if(hitTerrainSector(intersected_[0], pickRay, trees_, &count_, &done_))
				{
					if(!done_)
					{
						for(int i = 0; i < count_; i++) intersected_.push_back(trees_[i]);
						intersected_.erase(intersected_.begin());
					}
					else
					{
						rayAabbIntersected->push_back(intersected_[0]);
						intersected_.erase(intersected_.begin());
					}
				}
				else
					intersected_.erase(intersected_.begin());
			}

			// по расстоянию до камеры! сортировать
			//quick_sort(&realIntersected_, 0, realIntersected_.size() - 1);
		}

	#pragma endregion
	void RedactorTerrainManager::setTerraPenSize(int in, int out)
	{
		_heightPen->setSizeIn(in);_heightPen->setSizeOut(out);
	}
	void RedactorTerrainManager::setTerraPenHard(float hard)
	{
		_heightPen->hard = hard;
	}
	void RedactorTerrainManager::setTerraPenSmoothKoeff(float smoothKoeff)
	{
		_heightPen->smoothKoeff = smoothKoeff;
	}
	inline int RedactorTerrainManager::_getLeftTerrainIDValue(int vId, int currentRaw, int size)
	{ 
		int value = vId - size;
		if(value / _props.numVertsInRaw != currentRaw)
			value = currentRaw * _props.numVertsInRaw;
		if(value < 0) value = 0; 
		return value; 
	};
	inline int RedactorTerrainManager::_getRightTerrainIDValue(int vId, int currentRaw, int size)
	{ 
		int value = vId + size + 1;
		if(value / _props.numVertsInRaw != currentRaw)
			value = (currentRaw + 1) * _props.numVertsInRaw - 1;
		if(value > _props.maxId) 
			value = _props.maxId - 1;
		return value; 
	};
	inline int RedactorTerrainManager::_getUpTerrainIDValue(int vId, int size)
	{ 
		int value = vId - (size)* _props.numVertsInRaw;
		if(value < 0)
			value = vId - (vId / _props.numVertsInRaw) * _props.numVertsInRaw;
		return value;
	};
	inline int RedactorTerrainManager::_getDownTerrainIDValue(int vId, int size)
	{ 
		int value = vId + (size + 1) * _props.numVertsInRaw;
		if(value > _props.maxId) value = _props.maxId - 1;
		return value;
	};
	int4 RedactorTerrainManager::_getLRUD(int vId, int currentRaw, int size)
	{
		int left_ = _getLeftTerrainIDValue(vId, currentRaw, size);
		int right_ = _getRightTerrainIDValue(vId, currentRaw, size);

		int sizeX_ = right_ - left_;
		left_ = _getUpTerrainIDValue(left_, size);
		right_ = _getDownTerrainIDValue(right_, size);
		int sizeY_ = right_ / _props.numVertsInRaw - left_ / _props.numVertsInRaw;

		return int4(left_, right_, sizeX_, sizeY_);
	}
	void RedactorTerrainManager::_terraformShow(int terrainId, int vertId)
	{
		int currentRaw_ = vertId / _props.numVertsInRaw;

		int4 inStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeIn() - 1);
		int4 outStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeOut() - 1);
		int penOut_ = (outStruct_.z + 1) * (outStruct_.w + 1);
		int penIn_ = (inStruct_.z + 1) * (inStruct_.w + 1);

		int rawDisp_ = 0;
		for(int i = 0; i < penOut_; i++)
		{
			if(i != 0 && i % (outStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (outStruct_.z + 1);
			
			_heightPen->vertsOut_x[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].x;
			_heightPen->vertsOut_y[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].y;
			_heightPen->vertsOut_z[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].z;
		}
		_heightPen->countDrawSizeOut = penOut_;

		rawDisp_ = 0;
		for(int i = 0; i < penIn_; i++)
		{
			if(i != 0 && i % (inStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (inStruct_.z + 1);
			_heightPen->vertsIn_x[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].x;
			_heightPen->vertsIn_y[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].y;
			_heightPen->vertsIn_z[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].z;
		}
		_heightPen->countDrawSizeIn = penIn_;

		_heightPen->update();
	}
	void RedactorTerrainManager::_terraformApply(int terrainId, int vertId)
	{
		int currentRaw_ = vertId / _props.numVertsInRaw;

		int4 normalStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeOut());
		int4 inStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeIn() - 1);
		int4 outStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeOut() - 1);
		int penNormal_ = (normalStruct_.z + 1) * (normalStruct_.w + 1);
		int penOut_ = (outStruct_.z + 1) * (outStruct_.w + 1);
		int penIn_ = (inStruct_.z + 1) * (inStruct_.w + 1);

		int* temp_ = 0;		int* TerarainIDs_ = 0; int* SectorsIDs_ = 0;
		int countTerrainsToUpdate_ = 0;	int countSectorsToUpdate_ = 0;
		int rawDisp_ = 0;
		vector<int> needToRenormal_;

		for(int i = 0; i < penNormal_; i++)
		{
			if(i != 0 && i % (normalStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (normalStruct_.z + 1);
			needToRenormal_.push_back(normalStruct_.x + i + rawDisp_);
#pragma region TerrainIDs update
			int counter_ = 0;
			for(int q = 0; q < _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][0]; q++)
			{
				_vertsToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]][_countVertToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]]] = _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 2];
				_countVertToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]]++;
				bool add_ = true;
				for(int tt = 0; tt<countTerrainsToUpdate_; tt++)
				{
					if(TerarainIDs_[tt] == _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1])
					{
						add_ = false;
						break;
					}
				}
				if(add_)
				{
					temp_ = TerarainIDs_;			TerarainIDs_ = new int[countTerrainsToUpdate_ + 1];
					for(int tt = 0; tt<countTerrainsToUpdate_; tt++)			TerarainIDs_[tt] = temp_[tt];
					TerarainIDs_[countTerrainsToUpdate_] = _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1];
					countTerrainsToUpdate_++;
				}
				counter_ += 2;
			}
#pragma endregion
#pragma region TerrainSectors update
			counter_ = 0;
			for(int q = 0; q < _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][0]; q++)
			{	bool add_ = true;
				for(int tt = 0; tt<countSectorsToUpdate_; tt++)
				{
					if(SectorsIDs_[tt] == _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][counter_ + 1]){add_ = false;break;}
				}
				if(add_)
				{
					temp_ = SectorsIDs_;			SectorsIDs_ = new int[countSectorsToUpdate_ + 1];
					for(int tt = 0; tt<countSectorsToUpdate_; tt++)			SectorsIDs_[tt] = temp_[tt];
					SectorsIDs_[countSectorsToUpdate_] = _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][counter_ + 1];
					countSectorsToUpdate_++;
				}
				counter_ += 2;
			}
#pragma endregion
		}
		rawDisp_ = 0;
		for(int i = 0; i < penOut_; i++)
		{
			if(i != 0 && i % (outStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (outStruct_.z + 1);
			_props.heightMap[outStruct_.x + i + rawDisp_].y += _heightPen->hard;

			_heightPen->vertsOut_x[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].x;
			_heightPen->vertsOut_y[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].y;
			_heightPen->vertsOut_z[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].z;
		}
		_heightPen->countDrawSizeOut = penOut_;

		rawDisp_ = 0;
		for(int i = 0; i < penIn_; i++)
		{
			if(i != 0 && i % (inStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (inStruct_.z + 1);
			_props.heightMap[inStruct_.x + i + rawDisp_].y += _heightPen->hard;
		
			_heightPen->vertsIn_x[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].x;
			_heightPen->vertsIn_y[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].y;
			_heightPen->vertsIn_z[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].z;
		}
		_heightPen->countDrawSizeIn = penIn_;

		_heightPen->update();

		_renormal(&needToRenormal_, normalStruct_.z);
		for(int i = 0; i < countSectorsToUpdate_; i++)			_updateSector(SectorsIDs_[i]);
		for(int i = 0; i < countTerrainsToUpdate_; i++)			_updateSubVertexBuffer(TerarainIDs_[i]);

		delete SectorsIDs_; SectorsIDs_ = 0;
		delete TerarainIDs_; TerarainIDs_ = 0;
		delete temp_; temp_ = 0;
		needToRenormal_.clear();
	}
	void RedactorTerrainManager::_renormal(vector<int>* ids, int sizeX)
	{	
		for(int i = 0; i < ids->size() - sizeX; i++)
		{
			if((ids[0][i] / _props.numVertsInRaw == ids[0][i + 1] / _props.numVertsInRaw) && (ids[0][i + sizeX] < _props.maxId))
			{
				XMVECTOR AB = XMVectorSubtract(XMLoadFloat3(&_props.heightMap[ids[0][i + 1]]), XMLoadFloat3(&_props.heightMap[ids[0][i]]));
				XMVECTOR AC = XMVectorSubtract(XMLoadFloat3(&_props.heightMap[ids[0][i + sizeX]]), XMLoadFloat3(&_props.heightMap[ids[0][i]]));

				XMStoreFloat3(&_props.normalMap[ids[0][i]], XMVector3Normalize(XMVector3Cross(AB, AC)));
			}
		}
	}
	void RedactorTerrainManager::_terraformApplySmIn(int terrainId, int vertId)
	{
	#pragma region prepare work
		int currentRaw_ = vertId / _props.numVertsInRaw;

		int4 normalStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeOut());
		int4 inStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeIn() - 1);
		int4 outStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeOut() - 1);
		int penNormal_ = (normalStruct_.z + 1) * (normalStruct_.w + 1);
		int penOut_ = (outStruct_.z + 1) * (outStruct_.w + 1);
		int penIn_ = (inStruct_.z + 1) * (inStruct_.w + 1);

		int* temp_ = 0;		int* TerarainIDs_ = 0; int* SectorsIDs_ = 0;
		int countTerrainsToUpdate_ = 0;	int countSectorsToUpdate_ = 0;
		int rawDisp_ = 0;
		vector<int> needToRenormal_;
	#pragma endregion

		for(int i = 0; i < penNormal_; i++)
		{
			if(i != 0 && i % (normalStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (normalStruct_.z + 1);
			needToRenormal_.push_back(normalStruct_.x + i + rawDisp_);
	#pragma region TerrainIDs update
			int counter_ = 0;
			for(int q = 0; q < _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][0]; q++)
			{
				_vertsToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]][_countVertToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]]] = _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 2];
				_countVertToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]]++;
				bool add_ = true;
				for(int tt = 0; tt<countTerrainsToUpdate_; tt++)
				{
					if(TerarainIDs_[tt] == _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1])
					{
						add_ = false;
						break;
					}
				}
				if(add_)
				{
					temp_ = TerarainIDs_;			TerarainIDs_ = new int[countTerrainsToUpdate_ + 1];
					for(int tt = 0; tt<countTerrainsToUpdate_; tt++)			TerarainIDs_[tt] = temp_[tt];
					TerarainIDs_[countTerrainsToUpdate_] = _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1];
					countTerrainsToUpdate_++;
				}
				counter_ += 2;
			}
	#pragma endregion
	#pragma region TerrainSectors update
			counter_ = 0;
			for(int q = 0; q < _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][0]; q++)
			{
				bool add_ = true;
				for(int tt = 0; tt<countSectorsToUpdate_; tt++)
				{
					if(SectorsIDs_[tt] == _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][counter_ + 1]){ add_ = false; break; }
				}
				if(add_)
				{
					temp_ = SectorsIDs_;			SectorsIDs_ = new int[countSectorsToUpdate_ + 1];
					for(int tt = 0; tt<countSectorsToUpdate_; tt++)			SectorsIDs_[tt] = temp_[tt];
					SectorsIDs_[countSectorsToUpdate_] = _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][counter_ + 1];
					countSectorsToUpdate_++;
				}
				counter_ += 2;
			}
	#pragma endregion
		}	rawDisp_ = 0;
		for(int i = 0; i < penOut_; i++)
		{
			if(i != 0 && i % (outStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (outStruct_.z + 1);
			_props.heightMap[outStruct_.x + i + rawDisp_].y += _heightPen->hard;

			_heightPen->vertsOut_x[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].x;
			_heightPen->vertsOut_y[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].y;
			_heightPen->vertsOut_z[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].z;
		}
		_heightPen->countDrawSizeOut = penOut_;

		rawDisp_ = 0;
		for(int i = 0; i < penIn_; i++)
		{
			if(i != 0 && i % (inStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (inStruct_.z + 1);
			_props.heightMap[inStruct_.x + i + rawDisp_].y += _heightPen->hard;
		}rawDisp_ = 0;
		for(int i = 0; i < penIn_; i++)
		{
			if(i != 0 && i % (inStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (inStruct_.z + 1);
			_smoothVert(inStruct_.x + i + rawDisp_);

			_heightPen->vertsIn_x[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].x;
			_heightPen->vertsIn_y[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].y;
			_heightPen->vertsIn_z[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].z;
		}
		_heightPen->countDrawSizeIn = penIn_;
		_heightPen->update();

		_renormal(&needToRenormal_, normalStruct_.z);
		for(int i = 0; i < countSectorsToUpdate_; i++)			_updateSector(SectorsIDs_[i]);
		for(int i = 0; i < countTerrainsToUpdate_; i++)			_updateSubVertexBuffer(TerarainIDs_[i]);

		delete SectorsIDs_; SectorsIDs_ = 0;
		delete TerarainIDs_; TerarainIDs_ = 0;
		delete temp_; temp_ = 0;
		needToRenormal_.clear();
	}
	void RedactorTerrainManager::_terraformApplySmOut(int terrainId, int vertId)
	{
#pragma region prepare work
		int currentRaw_ = vertId / _props.numVertsInRaw;

		int4 normalStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeOut());
		int4 inStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeIn() - 1);
		int4 outStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeOut() - 1);
		int penNormal_ = (normalStruct_.z + 1) * (normalStruct_.w + 1);
		int penOut_ = (outStruct_.z + 1) * (outStruct_.w + 1);
		int penIn_ = (inStruct_.z + 1) * (inStruct_.w + 1);

		int* temp_ = 0;		int* TerarainIDs_ = 0; int* SectorsIDs_ = 0;
		int countTerrainsToUpdate_ = 0;	int countSectorsToUpdate_ = 0;
		int rawDisp_ = 0;
		vector<int> needToRenormal_;
#pragma endregion

		for(int i = 0; i < penNormal_; i++)
		{
			if(i != 0 && i % (normalStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (normalStruct_.z + 1);
			needToRenormal_.push_back(normalStruct_.x + i + rawDisp_);
#pragma region TerrainIDs update
			int counter_ = 0;
			for(int q = 0; q < _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][0]; q++)
			{
				_vertsToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]][_countVertToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]]] = _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 2];
				_countVertToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]]++;
				bool add_ = true;
				for(int tt = 0; tt<countTerrainsToUpdate_; tt++)
				{
					if(TerarainIDs_[tt] == _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1])
					{
						add_ = false;
						break;
					}
				}
				if(add_)
				{
					temp_ = TerarainIDs_;			TerarainIDs_ = new int[countTerrainsToUpdate_ + 1];
					for(int tt = 0; tt<countTerrainsToUpdate_; tt++)			TerarainIDs_[tt] = temp_[tt];
					TerarainIDs_[countTerrainsToUpdate_] = _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1];
					countTerrainsToUpdate_++;
				}
				counter_ += 2;
			}
#pragma endregion
#pragma region TerrainSectors update
			counter_ = 0;
			for(int q = 0; q < _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][0]; q++)
			{
				bool add_ = true;
				for(int tt = 0; tt<countSectorsToUpdate_; tt++)
				{
					if(SectorsIDs_[tt] == _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][counter_ + 1]){ add_ = false; break; }
				}
				if(add_)
				{
					temp_ = SectorsIDs_;			SectorsIDs_ = new int[countSectorsToUpdate_ + 1];
					for(int tt = 0; tt<countSectorsToUpdate_; tt++)			SectorsIDs_[tt] = temp_[tt];
					SectorsIDs_[countSectorsToUpdate_] = _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][counter_ + 1];
					countSectorsToUpdate_++;
				}
				counter_ += 2;
			}
#pragma endregion
		}	rawDisp_ = 0;
		vector<int> penInInds_;
		vector<int> penOutInds_;
		for(int i = 0; i < penIn_; i++)
		{
			if(i != 0 && i % (inStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (inStruct_.z + 1);
			_props.heightMap[inStruct_.x + i + rawDisp_].y += _heightPen->hard;
			penInInds_.push_back(inStruct_.x + i + rawDisp_);

			_heightPen->vertsIn_x[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].x;
			_heightPen->vertsIn_y[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].y;
			_heightPen->vertsIn_z[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].z;
		}rawDisp_ = 0;

		for(int i = 0; i < penOut_; i++)
		{
			if(i != 0 && i % (outStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (outStruct_.z + 1);
			_props.heightMap[outStruct_.x + i + rawDisp_].y += _heightPen->hard;
			if(!_vectorConains(&penInInds_, outStruct_.x + i + rawDisp_))
				penOutInds_.push_back(outStruct_.x + i + rawDisp_);
		}rawDisp_ = 0;

		for(int i = 0; i < penOutInds_.size(); i++)
			_smoothVert(penOutInds_[i]);
		
		for(int i = 0; i < penOut_; i++)
		{
			if(i != 0 && i % (outStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (outStruct_.z + 1);
			_heightPen->vertsOut_x[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].x;
			_heightPen->vertsOut_y[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].y;
			_heightPen->vertsOut_z[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].z;
		}rawDisp_ = 0;

		_heightPen->countDrawSizeOut = penOut_;
		_heightPen->countDrawSizeIn = penIn_;
		_heightPen->update();

		_renormal(&needToRenormal_, normalStruct_.z);
		for(int i = 0; i < countSectorsToUpdate_; i++)			_updateSector(SectorsIDs_[i]);
		for(int i = 0; i < countTerrainsToUpdate_; i++)			_updateSubVertexBuffer(TerarainIDs_[i]);

		delete SectorsIDs_; SectorsIDs_ = 0;
		delete TerarainIDs_; TerarainIDs_ = 0;
		delete temp_; temp_ = 0;
		needToRenormal_.clear();
		penInInds_.clear();
		penOutInds_.clear();
	}
	void RedactorTerrainManager::_terraformApplySmInOut(int terrainId, int vertId)
	{
#pragma region prepare work
		int currentRaw_ = vertId / _props.numVertsInRaw;

		int4 normalStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeOut());
		int4 inStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeIn() - 1);
		int4 outStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeOut() - 1);
		int penNormal_ = (normalStruct_.z + 1) * (normalStruct_.w + 1);
		int penOut_ = (outStruct_.z + 1) * (outStruct_.w + 1);
		int penIn_ = (inStruct_.z + 1) * (inStruct_.w + 1);

		int* temp_ = 0;		int* TerarainIDs_ = 0; int* SectorsIDs_ = 0;
		int countTerrainsToUpdate_ = 0;	int countSectorsToUpdate_ = 0;
		int rawDisp_ = 0;
		vector<int> needToRenormal_;
#pragma endregion

		for(int i = 0; i < penNormal_; i++)
		{
			if(i != 0 && i % (normalStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (normalStruct_.z + 1);
			needToRenormal_.push_back(normalStruct_.x + i + rawDisp_);
#pragma region TerrainIDs update
			int counter_ = 0;
			for(int q = 0; q < _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][0]; q++)
			{
				_vertsToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]][_countVertToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]]] = _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 2];
				_countVertToUpdate[_props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1]]++;
				bool add_ = true;
				for(int tt = 0; tt<countTerrainsToUpdate_; tt++)
				{
					if(TerarainIDs_[tt] == _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1])
					{
						add_ = false;
						break;
					}
				}
				if(add_)
				{
					temp_ = TerarainIDs_;			TerarainIDs_ = new int[countTerrainsToUpdate_ + 1];
					for(int tt = 0; tt<countTerrainsToUpdate_; tt++)			TerarainIDs_[tt] = temp_[tt];
					TerarainIDs_[countTerrainsToUpdate_] = _props.heightMapToTerrain[normalStruct_.x + i + rawDisp_][counter_ + 1];
					countTerrainsToUpdate_++;
				}
				counter_ += 2;
			}
#pragma endregion
#pragma region TerrainSectors update
			counter_ = 0;
			for(int q = 0; q < _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][0]; q++)
			{
				bool add_ = true;
				for(int tt = 0; tt<countSectorsToUpdate_; tt++)
				{
					if(SectorsIDs_[tt] == _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][counter_ + 1]){ add_ = false; break; }
				}
				if(add_)
				{
					temp_ = SectorsIDs_;			SectorsIDs_ = new int[countSectorsToUpdate_ + 1];
					for(int tt = 0; tt<countSectorsToUpdate_; tt++)			SectorsIDs_[tt] = temp_[tt];
					SectorsIDs_[countSectorsToUpdate_] = _props.heightMapToSectors[normalStruct_.x + i + rawDisp_][counter_ + 1];
					countSectorsToUpdate_++;
				}
				counter_ += 2;
			}
#pragma endregion
		}	rawDisp_ = 0;
		for(int i = 0; i < penOut_; i++)
		{
			if(i != 0 && i % (outStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (outStruct_.z + 1);
			_props.heightMap[outStruct_.x + i + rawDisp_].y += _heightPen->hard;
		}rawDisp_ = 0;
		for(int i = 0; i < penOut_; i++)
		{
			if(i != 0 && i % (outStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (outStruct_.z + 1);
			_smoothVert(outStruct_.x + i + rawDisp_);

			_heightPen->vertsOut_x[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].x;
			_heightPen->vertsOut_y[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].y;
			_heightPen->vertsOut_z[i] = &_props.heightMap[outStruct_.x + i + rawDisp_].z;
		}
		_heightPen->countDrawSizeOut = penOut_;

		rawDisp_ = 0;
		for(int i = 0; i < penIn_; i++)
		{
			if(i != 0 && i % (inStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (inStruct_.z + 1);
			_props.heightMap[inStruct_.x + i + rawDisp_].y += _heightPen->hard;

			_heightPen->vertsIn_x[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].x;
			_heightPen->vertsIn_y[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].y;
			_heightPen->vertsIn_z[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].z;
		}
		_heightPen->countDrawSizeIn = penIn_;
		_heightPen->update();

		_renormal(&needToRenormal_, normalStruct_.z);
		for(int i = 0; i < countSectorsToUpdate_; i++)			_updateSector(SectorsIDs_[i]);
		for(int i = 0; i < countTerrainsToUpdate_; i++)			_updateSubVertexBuffer(TerarainIDs_[i]);

		delete SectorsIDs_; SectorsIDs_ = 0;
		delete TerarainIDs_; TerarainIDs_ = 0;
		delete temp_; temp_ = 0;
		needToRenormal_.clear();
	}
	void RedactorTerrainManager::_updateSector(int idSector)
	{
		for(int i = 0; i < _countVertToUpdate[_props.sectors[idSector]->terrainId]; i++)
			_props.sectors[idSector]->checkMaxMinHeight(_props.heightMap[_props.pickToHeightMap[_props.sectors[idSector]->terrainId][_vertsToUpdate[_props.sectors[idSector]->terrainId][i]]].y);

		_props.sectors[idSector]->father->updateMatrix();
		_props.sectors[idSector]->father->updateInside();
	}

	void RedactorTerrainManager::_textureWork(int terrainId, float2 texcoord)
	{

	}
	bool RedactorTerrainManager::generate(int gridX, int gridY)
	{
		_props = Properties(gridX, gridY);
		_generateGeometry();

		delete _countVertToUpdate; delete[] _vertsToUpdate;
		_vertsToUpdate = new int*[_props.numTiles];
		_countVertToUpdate = new int[_props.numTiles];
		for(int i = 0; i<_props.numTiles; i++)
		{
			_countVertToUpdate[i] = 0;
			_vertsToUpdate[i] = new int[/*_heightPen->maxSize * _heightPen->maxSize*/100 * 4];
		}

		D3DX11_IMAGE_LOAD_INFO ili_;
		ili_.MipLevels = 1;
		ili_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		ili_.Width = 2048;
		ili_.Height = 2048;
		ili_.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		ili_.CpuAccessFlags = 0;
		ili_.MipFilter = D3D11_FILTER_TYPE_LINEAR;
		//ili_.FirstMipLevel = ResourceOptionFlags.None;
		ili_.MiscFlags = 0;
		ili_.Usage = D3D11_USAGE_DEFAULT;

		_textures = new ID3D11ShaderResourceView*[_props.numTiles];
		for(int i = 0; i < _props.numTiles; i++)
			D3dRender::getInstance().createTexture(_2048Path, &ili_, &_textures[i]);

		D3dRender::getInstance().setTerrainModels(_vertexBuffers, _textures, _props.numTiles, _indexBuffer, _props.numIndex);
		return true;
	}
	void RedactorTerrainManager::_smoothVert(int id)
	{
		int count = 0;
		float Main_height = _props.heightMap[id].y;
		float all_height = 0.0f;
		bool left = ((id - 1) / _props.numVertsInRaw == (id) / _props.numVertsInRaw) && (id>0);
		bool right = ((id + 1) / _props.numVertsInRaw == (id) / _props.numVertsInRaw) && (id < _props.maxId);
		if(id - _props.numVertsInRaw > 0)
		{
			all_height += _props.heightMap[id - _props.numVertsInRaw].y;
			count++;
			if(left)
			{
				count++;
				all_height += _props.heightMap[id - _props.numVertsInRaw - 1].y;
			}
			if(right)
			{
				count++;
				all_height += _props.heightMap[id - _props.numVertsInRaw + 1].y;
			}
		}
		if(left)
		{
			count++;
			all_height += _props.heightMap[id - 1].y;
		}
		if(right)
		{
			count++;
			all_height += _props.heightMap[id + 1].y;
		}
		if(id + _props.numVertsInRaw < _props.maxId)
		{
			all_height += _props.heightMap[id + _props.numVertsInRaw].y;
			count++;
			if(left)
			{
				count++;
				all_height += _props.heightMap[id + _props.numVertsInRaw - 1].y;
			}
			if(right)
			{
				count++;
				all_height += _props.heightMap[id + _props.numVertsInRaw + 1].y;
			}
		}
		_props.heightMap[id].y = (all_height / (float)count)*_heightPen->smoothKoeff + Main_height*(1.0f - _heightPen->smoothKoeff);
	}
	void RedactorTerrainManager::_updateSubVertexBuffer(int idTerrain)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource_;
		D3dRender::getInstance().mapResource(_vertexBuffers[idTerrain], &mappedResource_, D3D11_MAP_WRITE_NO_OVERWRITE);

		auto pData = reinterpret_cast<Vertex::Simple*>(mappedResource_.pData);
		for(int i = 0; i < _countVertToUpdate[idTerrain]; i++)
		{
			pData[_vertsToUpdate[idTerrain][i]].position.y = _props.heightMap[_props.pickToHeightMap[idTerrain][_vertsToUpdate[idTerrain][i]]].y;
			pData[_vertsToUpdate[idTerrain][i]].normal.x = _props.normalMap[_props.pickToHeightMap[idTerrain][_vertsToUpdate[idTerrain][i]]].x;
			pData[_vertsToUpdate[idTerrain][i]].normal.y = _props.normalMap[_props.pickToHeightMap[idTerrain][_vertsToUpdate[idTerrain][i]]].y;
			pData[_vertsToUpdate[idTerrain][i]].normal.z = _props.normalMap[_props.pickToHeightMap[idTerrain][_vertsToUpdate[idTerrain][i]]].z;
		}
		D3dRender::getInstance().unmapResource(_vertexBuffers[idTerrain]);
		_countVertToUpdate[idTerrain] = 0;
	}
	void RedactorTerrainManager::_updateVertexBuffer(int idTerrain)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource_;
		D3dRender::getInstance().mapResource(_vertexBuffers[idTerrain], &mappedResource_, D3D11_MAP_WRITE_NO_OVERWRITE);
		auto pData = reinterpret_cast<Vertex::Simple*>(mappedResource_.pData);
		for(int i = 0; i < _props.numTileVerts; i++)
		{
			pData[i].position = _props.heightMap[_props.pickToHeightMap[idTerrain][i]];
			pData[i].normal = _props.normalMap[_props.pickToHeightMap[idTerrain][i]];
		}
		D3dRender::getInstance().unmapResource(_vertexBuffers[idTerrain]);
	}
	void RedactorTerrainManager::randomize(int diapazon)
	{
		int diapazon_half = diapazon / 2;

		for(int i = 0; i < _props.numSectors; i++)
		{
			int randBiomIndex_ = rand() % _bioms.size();
			float height_ = (float)((rand() % ((int)_bioms[randBiomIndex_].range*diapazon)) - _bioms[randBiomIndex_].halfRange*diapazon);
			
			_props.heightMap[_props.sectorsToHeightMap[i][0]].y = _bioms[randBiomIndex_].height + height_;
			_props.sectors[i]->setMaxMinHeight(_bioms[randBiomIndex_].height + height_);

			for(int j = 1; j < _props.numSectorVerts; j++)
			{
				height_ = (float)((rand() % ((int)_bioms[randBiomIndex_].range*diapazon)) - _bioms[randBiomIndex_].halfRange*diapazon);
				_props.heightMap[_props.sectorsToHeightMap[i][j]].y = _bioms[randBiomIndex_].height + height_;
				_props.sectors[i]->checkMaxMinHeight(_bioms[randBiomIndex_].height + height_);
			}
		}
		_quadTree->update();
		normalizeNormals();
		for(int i = 0; i < _props.numTiles; i++)
			_updateVertexBuffer(i);
	}
	void RedactorTerrainManager::normalizeNormals()
	{
		for(int i = 0; i < _props.numVertsInCol; i++)
		{
			for(int j = 0; j < _props.numVertsInRaw; j++)
			{
				int id = i * _props.numVertsInCol + j;
				if(((id) / _props.numVertsInCol == (id + 1) / _props.numVertsInCol)
					&& ((id + _props.numVertsInCol) < _props.maxId))
				{
					XMVECTOR AB = XMVectorSubtract(XMLoadFloat3(&_props.heightMap[id + 1]), XMLoadFloat3(&_props.heightMap[id]));
					XMVECTOR AC = XMVectorSubtract(XMLoadFloat3(&_props.heightMap[id + _props.numVertsInRaw]), XMLoadFloat3(&_props.heightMap[id]));

					XMStoreFloat3(&_props.normalMap[id], XMVector3Normalize(XMVector3Cross(AB, AC)));
				}
			}
		}
	}
	void RedactorTerrainManager::blurHeightmap(int blurHard)
	{
		for(int rep = 0; rep < blurHard; rep++)
		{
			for(int i = 0; i < _props.numSectors; i++)
			{
				_smoothVert(_props.sectorsToHeightMap[i][0]);
				_props.sectors[i]->setMaxMinHeight(_props.heightMap[_props.sectorsToHeightMap[i][0]].y);

				for(int j = 1; j < _props.numSectorVerts; j++)
				{
					_smoothVert(_props.sectorsToHeightMap[i][j]);
					_props.sectors[i]->checkMaxMinHeight(_props.heightMap[_props.sectorsToHeightMap[i][j]].y);
				}
			}
			/*
			for(int i = 0; i < _props.numVertsInCol; i++)
			{
				for(int j = 0; j < _props.numVertsInRaw; j++)
					smoothVert(i*_props.numVertsInRaw + j);
			}*/
		}
		_quadTree->update();
		normalizeNormals();
		for(int i = 0; i < _props.numTiles; i++)
			_updateVertexBuffer(i);
	}
	bool RedactorTerrainManager::saveToFile(string fileName)
	{
		tryOpenStream(fileName, "w");
		string textureFName_ = fileName.substr(0, fileName.length()-4);

		tryWriteInt(_props.numVerts); tryWriteFloat(_props.cellSpace);
		Parser::getInstance().newLine();
		tryWriteInt(_props.sizeX); tryWriteInt(_props.sizeY);
		Parser::getInstance().newLine();
		for(int ter_i = 0; ter_i < _props.sizeX; ter_i++)
		{
			for(int ter_j = 0; ter_j < _props.sizeY; ter_j++)
			{
				for(int i = 0; i < _props.numVerts; i++)
				{
					for(int j = 0; j < _props.numVerts; j++)
					{
						tryWriteFloat(_props.heightMap[_props.pickToHeightMap[ter_i*_props.sizeX + ter_j][i*_props.numVerts + j]].y);
					}
					Parser::getInstance().newLine();
				}
				char str[4] = { '_', '_', '_', '_' };
				sprintf_s(str, "%d", ter_i*_props.sizeX + ter_j);
				ID3D11Resource* ress;		_textures[ter_i*_props.sizeX + ter_j]->GetResource(&ress);
				D3dRender::getInstance().saveResourceToFile(textureFName_ + str + ".dds", ress);
			}
		}
		tryCloseStream();

		return true;
	}
	void RedactorTerrainManager::set2048Path(string path)
	{
		_2048Path = path;
	}


	#pragma region Intersect work
		bool RedactorTerrainManager::hitTerrainSector(QuadTree* tree, precomputeRay* pickRay, QuadTree** hits, int* count, bool* done)
		{
			if(tree->intersect(pickRay))
			{
				if(!tree->land)
				{
					count[0] = tree->childs.size();
					for(int i = 0; i < count[0]; i++)
						hits[i] = tree->childs[i];

					done[0] = false;
					return true;
				}
				else
				{
					done[0] = true;
					return true;
				}
			}
			else
			{
				done[0] = true;
				return false;
			}
		}
		bool RedactorTerrainManager::_getQuadIntersectID(TerrainSector* sector, float3* pickDir, float3* pickOrig, int* returnedID)
		{
			int countIntersections = 0;
			float* connections = NULL;	int* connectionsID = NULL;
			int* tempID = NULL;	float* temp = NULL;

			XMFLOAT3** vs = new XMFLOAT3*[3];

			int dispForQuadVert_ = -1;
			for(int i = 0; i < _props.numSQuads; i++)
			{
				dispForQuadVert_++;
				for(int j = 0; j < _props.numSQuads; j++)
				{
				//for(int i = 0; i < _props.numSectorVerts; i++)
				//{
					vs[1] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + 0];
					vs[2] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + 1];
					vs[0] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + _props.numVertsInRaw];
					if(_intersectTriangle(pickOrig, pickDir, vs))
					{
						tempID = connectionsID;
						connectionsID = new int[countIntersections + 1];
						for(int i = 0; i<countIntersections; i++)
							connectionsID[i] = tempID[i];
						connectionsID[countIntersections] = _props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_];

						temp = connections;
						connections = new float[countIntersections + 1];
						for(int i = 0; i<countIntersections; i++)
							connections[i] = temp[i];
						connections[countIntersections] =
							sqrt((pickOrig->x - vs[0]->x)*(pickOrig->x - vs[0]->x)
							+ (pickOrig->y - vs[0]->y)*(pickOrig->y - vs[0]->y)
							+ (pickOrig->z - vs[0]->z)*(pickOrig->z - vs[0]->z));
						countIntersections++;
					}
					vs[0] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + 1];//Verts[id][indices[6 * i + 0]];
					vs[1] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + _props.numVertsInRaw + 1];
					vs[2] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + _props.numVertsInRaw];
					if(_intersectTriangle(pickOrig, pickDir, vs))
					{
						tempID = connectionsID;
						connectionsID = new int[countIntersections + 1];
						for(int i = 0; i<countIntersections; i++)
							connectionsID[i] = tempID[i];
						connectionsID[countIntersections] = _props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_];

						temp = connections;
						connections = new float[countIntersections + 1];
						for(int i = 0; i<countIntersections; i++)
							connections[i] = temp[i];
						connections[countIntersections] = 
							sqrt((pickOrig->x - vs[0]->x)*(pickOrig->x - vs[0]->x)
							+ (pickOrig->y - vs[0]->y)*(pickOrig->y - vs[0]->y)
							+ (pickOrig->z - vs[0]->z)*(pickOrig->z - vs[0]->z));
						countIntersections++;
					}
				}
			}
			delete vs;
			if(countIntersections == 0) return false;
			int idd = connectionsID[0];
			float min_dist = connections[0];
			for(int i = 1; i<countIntersections; i++)
			{
				if(connections[i]<min_dist)
				{
					min_dist = connections[i];
					idd = connectionsID[i];
				}
			}
			delete tempID; tempID = NULL;
			delete temp; temp = NULL;
			delete connections; connections = NULL;
			delete connectionsID; connectionsID = NULL;
			returnedID[0] = idd;// _props.quadVertConnect[idd];
			return	true;
		}
		bool RedactorTerrainManager::_getQuadIntersectID(TerrainSector* sector, float3* pickDir, float3* pickOrig, float* tu, float* tv)
		{
			float u; float v;
			int countIntersections = 0;
			float2* all_tutv = NULL;	float2* temp_tutv = NULL;
			float* connections = NULL;	float* temp = NULL;
			float3** vs = new float3*[3];
			int dispForQuadVert_ = -1;
			for(int i = 0; i < _props.numSQuads; i++)
			{
				dispForQuadVert_++;
				for(int j = 0; j < _props.numSQuads; j++)
				{
					vs[1] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + 0];
					vs[2] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + 1];
					vs[0] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + _props.numVertsInRaw];
					if(_intersectTriangle(pickOrig, pickDir, vs, &v, &u))
					{
						float raw = _props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] / _props.numQuad;
						float col = _props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] % _props.numQuad;
						u = u / (float)_props.numQuad + raw / (float)_props.numQuad;
						v = v / (float)_props.numQuad + col / (float)_props.numQuad;

						temp_tutv = all_tutv;
						all_tutv = new XMFLOAT2[countIntersections + 1];
						for(int i = 0; i < countIntersections; i++)
							all_tutv[i] = temp_tutv[i];
						all_tutv[countIntersections] = XMFLOAT2(u, v);

						temp = connections;
						connections = new float[countIntersections + 1];
						for(int i = 0; i < countIntersections; i++)
							connections[i] = temp[i];
						connections[countIntersections] =
							sqrt((pickOrig->x - vs[0]->x)*(pickOrig->x - vs[0]->x)
							+ (pickOrig->y - vs[0]->y)*(pickOrig->y - vs[0]->y)
							+ (pickOrig->z - vs[0]->z)*(pickOrig->z - vs[0]->z));
						countIntersections++;
					}
					vs[0] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + 1];//Verts[id][indices[6 * i + 0]];
					vs[1] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + _props.numVertsInRaw + 1];
					vs[2] = &_props.heightMap[_props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] + _props.numVertsInRaw];
					if(_intersectTriangle(pickOrig, pickDir, vs, &v, &u))
					{
						float raw = _props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] / _props.numQuad;
						float col = _props.sectorsToHeightMap[sector->id][i*_props.numSQuads + j + dispForQuadVert_] % _props.numQuad;
						u = (1.0f - u) / (float)_props.numQuad + raw / (float)_props.numQuad;
						v = (1.0f - v) / (float)_props.numQuad + col / (float)_props.numQuad;

						temp_tutv = all_tutv;
						all_tutv = new XMFLOAT2[countIntersections + 1];
						for(int i = 0; i < countIntersections; i++)
							all_tutv[i] = temp_tutv[i];
						all_tutv[countIntersections] = XMFLOAT2(u, v);

						temp = connections;
						connections = new float[countIntersections + 1];
						for(int i = 0; i < countIntersections; i++)
							connections[i] = temp[i];
						connections[countIntersections] =
							sqrt((pickOrig->x - vs[0]->x)*(pickOrig->x - vs[0]->x)
							+ (pickOrig->y - vs[0]->y)*(pickOrig->y - vs[0]->y)
							+ (pickOrig->z - vs[0]->z)*(pickOrig->z - vs[0]->z));
						countIntersections++;
					}
				}
			}
			delete vs;	vs = NULL;
			if(countIntersections == 0)			return false;

			XMFLOAT2 right_tutv = all_tutv[0];
			float min_dist = connections[0];
			for(int i = 1; i<countIntersections; i++)
			{
				if(connections[i]<min_dist)
				{
					min_dist = connections[i];
					right_tutv = all_tutv[i];
				}
			}
			delete temp; temp = NULL;
			delete connections; connections = NULL;
			delete temp_tutv; temp_tutv = NULL;
			delete all_tutv; all_tutv = NULL;

			tu[0] = right_tutv.x;
			tv[0] = right_tutv.y;

			return true;
		}
		bool RedactorTerrainManager::_intersectTriangle(float3* pickOrig, float3* pickDir, XMFLOAT3** vs)
		{
			float u = 0.0f, v = 0.0f, t = 0.0f;

			XMFLOAT3 edge1; XMFLOAT3 edge2;
			XMStoreFloat3(&edge1, XMVectorSubtract(XMLoadFloat3(vs[1]), XMLoadFloat3(vs[0])));
			XMStoreFloat3(&edge2, XMVectorSubtract(XMLoadFloat3(vs[2]), XMLoadFloat3(vs[0])));

			XMFLOAT3 pvec;
			XMStoreFloat3(&pvec, XMVector3Cross(XMLoadFloat3(pickDir), XMLoadFloat3(&edge2)));

			FLOAT det;
			XMStoreFloat(&det, XMVector3Dot(XMLoadFloat3(&edge1), XMLoadFloat3(&pvec)));
			XMFLOAT3 tvec;
			if(det > 0)
				XMStoreFloat3(&tvec, XMVectorSubtract(XMLoadFloat3(pickOrig), XMLoadFloat3(vs[0])));
			else
			{
				XMStoreFloat3(&tvec, XMVectorSubtract(XMLoadFloat3(vs[0]), XMLoadFloat3(pickOrig)));
				det = -det;
			}

			if(det < 0.0001f)
				return FALSE;

			// Calculate U parameter and test bounds
			XMStoreFloat(&u, XMVector3Dot(XMLoadFloat3(&tvec), XMLoadFloat3(&pvec)));
			if(u < 0.0f || u > det)
				return FALSE;

			XMFLOAT3 qvec;
			XMStoreFloat3(&qvec, XMVector3Cross(XMLoadFloat3(&tvec), XMLoadFloat3(&edge1)));

			XMStoreFloat(&v, XMVector3Dot(XMLoadFloat3(pickDir), XMLoadFloat3(&qvec)));
			if(v < 0.0f || u + v > det)
				return FALSE;

			return TRUE;
		}
		bool RedactorTerrainManager::_intersectTriangle(float3* pickOrig, float3* pickDir, XMFLOAT3** vs, float* tu, float* tv)
		{
			XMFLOAT3 edge1; XMFLOAT3 edge2;
			XMStoreFloat3(&edge1, XMVectorSubtract(XMLoadFloat3(vs[1]), XMLoadFloat3(vs[0])));
			XMStoreFloat3(&edge2, XMVectorSubtract(XMLoadFloat3(vs[2]), XMLoadFloat3(vs[0])));

			XMFLOAT3 pvec;
			XMStoreFloat3(&pvec, XMVector3Cross(XMLoadFloat3(pickDir), XMLoadFloat3(&edge2)));

			FLOAT det;
			XMStoreFloat(&det, XMVector3Dot(XMLoadFloat3(&edge1), XMLoadFloat3(&pvec)));
			XMFLOAT3 tvec;
			if(det > 0)
				XMStoreFloat3(&tvec, XMVectorSubtract(XMLoadFloat3(pickOrig), XMLoadFloat3(vs[0])));
			else
			{
				XMStoreFloat3(&tvec, XMVectorSubtract(XMLoadFloat3(vs[0]), XMLoadFloat3(pickOrig)));
				det = -det;
			}

			if(det < 0.0001f)
				return FALSE;

			// Calculate U parameter and test bounds
			XMStoreFloat(tu, XMVector3Dot(XMLoadFloat3(&tvec), XMLoadFloat3(&pvec)));
			if(tu[0] < 0.0f || tu[0] > det)
				return FALSE;

			XMFLOAT3 qvec;
			XMStoreFloat3(&qvec, XMVector3Cross(XMLoadFloat3(&tvec), XMLoadFloat3(&edge1)));

			XMStoreFloat(tv, XMVector3Dot(XMLoadFloat3(pickDir), XMLoadFloat3(&qvec)));
			if(tv[0] < 0.0f || tu[0] + tv[0] > det)
				return FALSE;

			// Calculate t, scale parameters, ray intersects triangle
			//XMStoreFloat(&t, XMVector3Dot( XMLoadFloat3(&edge2), XMLoadFloat3(&qvec) ));
			FLOAT fInvDet = 1.0f / det;
			//t *= fInvDet;
			*tu *= fInvDet;
			*tv *= fInvDet;

			return TRUE;
		}
	#pragma endregion

#pragma endregion

#pragma region diamondSquare
		float RedactorTerrainManager::_dist(float3 point1, float3 point2)
		{
			return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2) + pow(point2.z - point1.z, 2));
		}
		void RedactorTerrainManager::diamondSquareAlgorythm()
		{
		#pragma region Lists
			vector<int> _1_;
			vector<int> _2_;
			vector<int> _3_;
			vector<int> _6_;

			vector<int> _11_;
			vector<int> _22_;

			vector<int> _43_;
			vector<int> _86_;

			vector<int> _171_;
			vector<int> _342_;
			
			for(int i = 0; i < 1023; i++)
			{
				_1_.push_back(i * 4 + 1);
				_1_.push_back(i * 4 + 3);

				_2_.push_back(i * 4 + 2);
				_2_.push_back(i * 4 + 3);
			}
			for(int i = 0; i < 511; i++)
			{
				_3_.push_back(i * 8 + 4);
				_3_.push_back(i * 8 + 6);
			}
			for(int i = 0; i < 255; i++)
			{
				_6_.push_back(i * 16 + 8);
				_6_.push_back(i * 16 + 9);

				_6_.push_back(i * 16 + 12);
				_6_.push_back(i * 16 + 13);
			}
			for(int i = 0; i < 127; i++)
			{
				_11_.push_back(i * 32 + 16);
				_11_.push_back(i * 32 + 18);

				_11_.push_back(i * 32 + 24);
				_11_.push_back(i * 32 + 26);
			}
			for(int i = 0; i < 63; i++)
			{
				_22_.push_back(i * 64 + 32);
				_22_.push_back(i * 64 + 33);

				_22_.push_back(i * 64 + 36);
				_22_.push_back(i * 64 + 37);

				_22_.push_back(i * 64 + 48);
				_22_.push_back(i * 64 + 49);

				_22_.push_back(i * 64 + 52);
				_22_.push_back(i * 64 + 53);
			}
			for(int i = 0; i < 31; i++)
			{
				_43_.push_back(i * 128 + 64);
				_43_.push_back(i * 128 + 66);

				_43_.push_back(i * 128 + 72);
				_43_.push_back(i * 128 + 74);

				_43_.push_back(i * 128 + 96);
				_43_.push_back(i * 128 + 98);

				_43_.push_back(i * 128 + 104);
				_43_.push_back(i * 128 + 106);
			}

			for(int i = 0; i < 15; i++)
			{
				_86_.push_back(i * 256 + 128);
				_86_.push_back(i * 256 + 129);

				_86_.push_back(i * 256 + 132);
				_86_.push_back(i * 256 + 133);

				_86_.push_back(i * 256 + 144);
				_86_.push_back(i * 256 + 145);

				_86_.push_back(i * 256 + 148);
				_86_.push_back(i * 256 + 149);

				_86_.push_back(i * 256 + 192);
				_86_.push_back(i * 256 + 193);

				_86_.push_back(i * 256 + 196);
				_86_.push_back(i * 256 + 197);

				_86_.push_back(i * 256 + 208);
				_86_.push_back(i * 256 + 209);

				_86_.push_back(i * 256 + 212);
				_86_.push_back(i * 256 + 213);
			}
			for(int i = 0; i < 7; i++)
			{
				_171_.push_back(i * 512 + 256);
				_171_.push_back(i * 512 + 258);

				_171_.push_back(i * 512 + 264);
				_171_.push_back(i * 512 + 266);

				_171_.push_back(i * 512 + 288);
				_171_.push_back(i * 512 + 290);

				_171_.push_back(i * 512 + 296);
				_171_.push_back(i * 512 + 298);

				_171_.push_back(i * 512 + 384);
				_171_.push_back(i * 512 + 386);

				_171_.push_back(i * 512 + 392);
				_171_.push_back(i * 512 + 394);

				_171_.push_back(i * 512 + 416);
				_171_.push_back(i * 512 + 418);

				_171_.push_back(i * 512 + 424);
				_171_.push_back(i * 512 + 426);
			}
			for(int i = 0; i < 3; i++)
			{
				_342_.push_back(i * 1024 + 512);
				_342_.push_back(i * 1024 + 513);
				_342_.push_back(i * 1024 + 516);
				_342_.push_back(i * 1024 + 516);

				_342_.push_back(i * 1024 + 528);
				_342_.push_back(i * 1024 + 529);
				_342_.push_back(i * 1024 + 532);
				_342_.push_back(i * 1024 + 533);

				_342_.push_back(i * 1024 + 576);
				_342_.push_back(i * 1024 + 577);
				_342_.push_back(i * 1024 + 580);
				_342_.push_back(i * 1024 + 581);

				_342_.push_back(i * 1024 + 592);
				_342_.push_back(i * 1024 + 593);
				_342_.push_back(i * 1024 + 596);
				_342_.push_back(i * 1024 + 597);

				_342_.push_back(i * 1024 + 768);
				_342_.push_back(i * 1024 + 769);
				_342_.push_back(i * 1024 + 772);
				_342_.push_back(i * 1024 + 773);

				_342_.push_back(i * 1024 + 784);
				_342_.push_back(i * 1024 + 785);
				_342_.push_back(i * 1024 + 788);
				_342_.push_back(i * 1024 + 789);

				_342_.push_back(i * 1024 + 832);
				_342_.push_back(i * 1024 + 833);
				_342_.push_back(i * 1024 + 836);
				_342_.push_back(i * 1024 + 837);

				_342_.push_back(i * 1024 + 848);
				_342_.push_back(i * 1024 + 849);
				_342_.push_back(i * 1024 + 852);
				_342_.push_back(i * 1024 + 853);
			}
#pragma endregion
			int curNumV_ = _props.numVerts;

			vector<Quad>* quads2_ = new vector<Quad>;
			vector<Quad>* quads_ = new vector<Quad>;
		#pragma region prepare for diamonSquare
			for(int i = 0; i < _props.numTiles; i++)
			{
				int randBiomIndex_ = rand() % _bioms.size();
				float height_ = (float)((rand() % ((int)_bioms[randBiomIndex_].range)) - _bioms[randBiomIndex_].halfRange);

				Quad tile_;
				_props.heightMap[_props.pickToHeightMap[i][(_props.numTileVerts / 2)]].y = height_;
				tile_.center = _props.numTileVerts / 2; //_props.pickToHeightMap[i][(_props.numTileVerts / 2)];
				tile_.tileId = i;

				tile_._1 = 0;
				tile_._2 = _props.numVerts - 1;
				tile_._3 = _props.numTileVerts - _props.numVerts;
				tile_._4 = _props.numTileVerts - 1;

				quads_->push_back(tile_);
			}

			for(int i = 0; i < _props.numTiles; i++)
			{
				float diap_ = _props.numVerts * _props.cellSpace * 2;
				int randBiomIndex_ = rand() % _bioms.size();
				float height_ = (float)((rand() % ((int)_bioms[randBiomIndex_].range)) - _bioms[randBiomIndex_].halfRange);

				if((quads_[0][i].tileId - 1) / _props.sizeX == quads_[0][i].tileId / _props.sizeX && quads_[0][i].tileId != 0)
				{
					quads_[0][i].left = _props.heightMap[_props.pickToHeightMap[quads_[0][i - 1].tileId][quads_[0][i - 1].center]].y;
					quads_[0][i].leftID = quads_[0][i - 1].center;
				}
				else
				{
					quads_[0][i].left = height_;
					randBiomIndex_ = rand() % _bioms.size();
					height_ = (float)((rand() % ((int)_bioms[randBiomIndex_].range)) - _bioms[randBiomIndex_].halfRange);
					quads_[0][i].leftID = -1;
				}
				if((quads_[0][i].tileId + 1) / _props.sizeX == quads_[0][i].tileId / _props.sizeX && quads_[0][i].tileId != _props.numTiles - 1)
				{
					quads_[0][i].right = _props.heightMap[_props.pickToHeightMap[quads_[0][i + 1].tileId][quads_[0][i + 1].center]].y;
					quads_[0][i].rightID = quads_[0][i + 1].center;
				}
				else
				{
					quads_[0][i].right = height_;
					randBiomIndex_ = rand() % _bioms.size();
					height_ = (float)((rand() % ((int)_bioms[randBiomIndex_].range)) - _bioms[randBiomIndex_].halfRange);
					quads_[0][i].rightID = -1;
				}
				if((quads_[0][i].tileId - _props.sizeX) >= 0)
				{
					quads_[0][i].up = _props.heightMap[_props.pickToHeightMap[quads_[0][i - _props.sizeX].tileId][quads_[0][i - _props.sizeX].center]].y;
					quads_[0][i].upID = quads_[0][i - _props.sizeX].center;
				}
				else
				{
					quads_[0][i].up = height_;
					randBiomIndex_ = rand() % _bioms.size();
					height_ = (float)((rand() % ((int)_bioms[randBiomIndex_].range)) - _bioms[randBiomIndex_].halfRange);
					quads_[0][i].upID = -1;
				}
				if((quads_[0][i].tileId + _props.sizeX) < _props.numTiles)
				{
					quads_[0][i].down = _props.heightMap[_props.pickToHeightMap[quads_[0][i + _props.sizeX].tileId][quads_[0][i + _props.sizeX].center]].y;
					quads_[0][i].downID = quads_[0][i + _props.sizeX].center;
				}
				else
				{
					quads_[0][i].down = height_;
					randBiomIndex_ = rand() % _bioms.size();
					height_ = (float)((rand() % ((int)_bioms[randBiomIndex_].range)) - _bioms[randBiomIndex_].halfRange);
					quads_[0][i].downID = -1;
				}

				height_ = (float)((rand() % ((int)diap_)) - diap_/2.0f);
				_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._1]].y =
					(_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i].center]].y + quads_[0][i].left + quads_[0][i].up) / 3.0f + height_;

				height_ = (float)((rand() % ((int)diap_)) - diap_ / 2.0f);
				_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._2]].y =
					(_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i].center]].y + quads_[0][i].right + quads_[0][i].up) / 3.0f + height_;

				height_ = (float)((rand() % ((int)diap_)) - diap_ / 2.0f);
				_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._4]].y =
					(_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i].center]].y + quads_[0][i].right + quads_[0][i].down) / 3.0f + height_;

				height_ = (float)((rand() % ((int)diap_)) - diap_ / 2.0f);
				_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._3]].y =
					(_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i].center]].y + quads_[0][i].down + quads_[0][i].left) / 3.0f + height_;

				quads_[0][i].diapazon = diap_;
			}
	#pragma endregion

			curNumV_ = _props.numQuad;
			int doubleCurNumV_ = curNumV_*curNumV_;

			for(int rep = 0; rep < 6; rep++)
			{
				for(int i = 0; i < quads_->size(); i++)
				{
				#pragma region WORKS correct
					float randValue_ = (float)(rand() % ((int)quads_[0][i].diapazon)) - (quads_[0][i].diapazon / 2.0f);
					_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i].center]].y =
						(_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._1]].y+
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._2]].y+
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._3]].y+
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._4]].y)/4.0f + randValue_;
					
					int centrLeft_ = quads_[0][i].center - curNumV_ / 2;
					int centrUp_ = quads_[0][i]._1 + curNumV_ / 2;
					int centrRight_ = quads_[0][i].center + curNumV_ / 2;
					int centrDown_ = quads_[0][i]._4 - curNumV_ / 2;
					
					float diamondDiap_ = sqrt(quads_[0][i].diapazon);
					randValue_ = (float)(rand() % ((int)diamondDiap_)) - (diamondDiap_ / 2.0f);
					_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][centrLeft_]].y =
						(_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i].center]].y +
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._1]].y +
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._3]].y +
						quads_[0][i].left)/4.0f + randValue_ ;

					_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][centrUp_]].y =
						(_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i].center]].y +
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._1]].y +
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._2]].y +
						quads_[0][i].up) / 4.0f + randValue_;

					_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][centrRight_]].y =
						(_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i].center]].y +
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._2]].y +
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._4]].y +
						quads_[0][i].right) / 4.0f + randValue_;

					_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][centrDown_]].y =
						(_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i].center]].y +
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._3]].y +
						_props.heightMap[_props.pickToHeightMap[quads_[0][i].tileId][quads_[0][i]._4]].y +
						quads_[0][i].down) / 4.0f + randValue_;

					Quad qd;qd._1 = quads_[0][i]._1;
					qd._2 = centrUp_;
					qd._4 = quads_[0][i].center;
					qd._3 = centrLeft_;
					qd.center = qd._1 + doubleCurNumV_ / 4 + curNumV_ / 2;
					qd.diapazon = quads_[0][i].diapazon / 2.0f;
					qd.tileId = quads_[0][i].tileId;

					Quad qd2;
					qd2._1 = centrUp_;
					qd2._2 = quads_[0][i]._2;
					qd2._3 = quads_[0][i].center;
					qd2._4 = centrRight_;
					qd2.center = qd.center + curNumV_ / 2;
					qd2.diapazon = quads_[0][i].diapazon / 2.0f;
					qd2.tileId = quads_[0][i].tileId;

					Quad qd3;
					qd3._1 = centrLeft_; 
					qd3._2 = quads_[0][i].center; 
					qd3._3 = quads_[0][i]._3;
					qd3._4 = centrDown_;
					qd3.center = qd3._1 + doubleCurNumV_ / 4 + curNumV_ / 2;
					
					qd3.diapazon = quads_[0][i].diapazon / 2.0f;
					qd3.tileId = quads_[0][i].tileId;

					Quad qd4;
					qd4._1 = quads_[0][i].center; 
					qd4._2 = centrRight_;
					qd4._3 = centrDown_;
					qd4._4 = quads_[0][i]._4;
					qd4.center = qd4._1 + doubleCurNumV_ / 4 + curNumV_ / 2;
					qd4.diapazon = quads_[0][i].diapazon / 2.0f;
					qd4.tileId = quads_[0][i].tileId;

					qd.right = _props.heightMap[_props.pickToHeightMap[qd2.tileId][qd2.center]].y; qd.rightID = qd2.center;
					qd.down = _props.heightMap[_props.pickToHeightMap[qd2.tileId][qd3.center]].y; qd.downID = qd3.center;
					qd2.left = _props.heightMap[_props.pickToHeightMap[qd2.tileId][qd.center]].y; qd2.leftID = qd.center;
					qd2.down = _props.heightMap[_props.pickToHeightMap[qd4.tileId][qd4.center]].y; qd2.downID = qd4.center;
					qd3.up = _props.heightMap[_props.pickToHeightMap[qd2.tileId][qd.center]].y; qd3.upID = qd.center;
					qd3.right = _props.heightMap[_props.pickToHeightMap[qd4.tileId][qd4.center]].y; qd3.rightID = qd4.center;
					qd4.left = _props.heightMap[_props.pickToHeightMap[qd4.tileId][qd3.center]].y; qd4.leftID = qd3.center;
					qd4.up = _props.heightMap[_props.pickToHeightMap[qd2.tileId][qd2.center]].y; qd4.upID = qd2.center;
				#pragma endregion
					quads2_->push_back(qd); quads2_->push_back(qd2); quads2_->push_back(qd3); quads2_->push_back(qd4);
					for(int q = 4; q > 0; q--)
						_setDSQuadProps(&quads2_[0][quads2_->size() - q], quads2_->size() - q, quads2_, &quads_[0][i],
						&_1_, &_2_, &_3_, &_6_, &_11_, &_22_, &_43_, &_86_, &_171_, &_342_);
				}
				doubleCurNumV_ /= 2;
				curNumV_ /= 2;
				quads_ = quads2_;
				quads2_ = new vector<Quad>;
			}
			quads_->clear();
			delete quads_;
			delete quads2_;
			for(int i = 0; i < _props.numTiles; i++)
			_updateVertexBuffer(i);
		}
		void RedactorTerrainManager::_setDSQuadProps(Quad* quad, int indexQuad, vector<Quad>* quads, Quad* father,
			vector<int>* _1, vector<int>* _2, vector<int>* _3, vector<int>* _6, vector<int>* _11, vector<int>* _22, 
			vector<int>* _43, vector<int>* _86, vector<int>* _171, vector<int>* _342)
		{
			if(father->rightID == -1){ quad->right = father->right; quad->rightID = -1; }
			if(father->downID == -1){ quad->down = father->down; quad->downID = -1; }
			if(father->leftID == -1){ quad->left = father->left; quad->leftID = -1; }
			else
			{
				int disp_ = 1;
				if(_vectorConains(_171, indexQuad)) disp_ = 171;
				else
				{
					if(_vectorConains(_43, indexQuad)) disp_ = 43;
					else
					{
						if(_vectorConains(_11, indexQuad)) disp_ = 11;
						else
						{
							if(_vectorConains(_3, indexQuad)) disp_ = 3;
						}
					}
				}
				quad->leftID = quads[0][indexQuad - disp_].center;
				quad->left = _props.heightMap[_props.pickToHeightMap[quads[0][indexQuad - disp_].tileId][quad->leftID]].y;
				quads[0][indexQuad - disp_].rightID = quad->center;
				quads[0][indexQuad - disp_].right = _props.heightMap[_props.pickToHeightMap[quads[0][indexQuad].tileId][quad->center]].y;
			}
			if(father->upID == -1){ quad->up = father->up; quad->upID = -1; }
			else
			{
				int disp_ = 2;
				if(_vectorConains(_342, indexQuad)) disp_ = 342;
				else
				{
					if(_vectorConains(_86, indexQuad)) disp_ = 86;
					else
					{
						if(_vectorConains(_22, indexQuad)) disp_ = 22;
						else
						{
							if(_vectorConains(_6, indexQuad)) disp_ = 6;
						}
					}
				}

				quad->upID = quads[0][indexQuad - disp_].center;
				quad->up = _props.heightMap[_props.pickToHeightMap[quads[0][indexQuad - disp_].tileId][quad->upID]].y;
				quads[0][indexQuad - disp_].downID = quad->center;
				quads[0][indexQuad - disp_].down = _props.heightMap[_props.pickToHeightMap[quads[0][indexQuad].tileId][quad->center]].y;
			}
		}
		bool RedactorTerrainManager::_vectorConains(vector<int>* vect, int value)
		{
			bool ret_ = false;

			for(int i = 0; i < vect->size(); i++)
			{
				if(vect[0][i] == value)
					return true;
			}
			return ret_;
		}
#pragma endregion

		/*
void quick_sort(vector <QuadTree*> &v, int begin0, int end0)
{
	auto d = end0;//число относительно 
	//которого будем сравнивать
	auto begin = begin0;//указатель на начало
	auto end = end0;//указатель на конец

	do
	{
		while(v[begin]->terrainSector-><d)
			begin++;
		while(v[end]>d)
			end--;
		if(begin <= end)
		{
			swap(v[begin], v[end]);// меняем местами
			begin++;
			end--;
		}
	} while(begin <= end);
	if(begin0<end)
		quick_sort(v, begin0, end);
	if(begin<end0)
		quick_sort(v, begin, end0);
}*/