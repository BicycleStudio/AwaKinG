#include "TerrainManager.h"


#pragma region main functions
	TerrainManager::TerrainManager()
	{
		_indexBuffer = NULL;
		_2048Path = "../../media/terrain/_2048.dds";
		_quadTree = NULL;
	}
	RedactorTerrainManager::RedactorTerrainManager()
	{
		_bioms.push_back(Biom(1000.0f, 250.0f));
		_bioms.push_back(Biom(500.0f, 100.0f));
		_bioms.push_back(Biom(100.0f, 50.0f));
		_bioms.push_back(Biom(10.0f, 100.0f));
		_bioms.push_back(Biom(10.0f, 10.0f));
		_bioms.push_back(Biom(-100.0f, 30.0f));
		_bioms.push_back(Biom(-250.0f, 75.0f));
		_indexBuffer = NULL; _workType = TWT_NONE;
		_2048Path = "../../../../media/terrain/_2048.dds";
		_quadTree = NULL;
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
			int dispRawLocal_ = 0;
			int dispTileStart = i % _props.sizeSectorX;
			if(dispTileStart == 0 && i != 0)
				dispRawGlob_ += _props.numVertsInRaw * _props.numSQuads;
			else
				dispTileStart *= _props.numSQuads;

			int savedI_ = 0; int savedJ_ = 0; int savedK_ = 0; int savedL_ = 0; int savedM_ = 0; int savedN_ = 0;
			for(int j = 0; j < _props.numSectorVerts; j++)
			{
				if(j % _props.numSVerts == 0 && j != 0) dispRawLocal_ += _props.numVertsInRaw - _props.numSVerts;

				_props.sectorsToHeightMap[i][j] = dispRawGlob_ + dispTileStart + j + dispRawLocal_;

				switch(_props.heightMapToSectors[dispRawGlob_ + dispTileStart + dispRawLocal_ + j][0])
				{
				case 0:
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_] = new int[3];
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][0] = 1;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][1] = i;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][2] = j;
					break;
				case 1:
					savedI_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][1];
					savedJ_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][2];

					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_] = new int[5];
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][0] = 2;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][1] = savedI_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][2] = savedJ_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][3] = i;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][4] = j;
					break;
				case 2:
					savedI_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][1];
					savedJ_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][2];
					savedK_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][3];
					savedL_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][4];

					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_] = new int[7];
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][0] = 3;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][1] = savedI_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][2] = savedJ_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][3] = savedK_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][4] = savedL_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][5] = i;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][6] = j;
					break;
				case 3:
					savedI_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][1];
					savedJ_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][2];
					savedK_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][3];
					savedL_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][4];
					savedM_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][5];
					savedN_ = _props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][6];

					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_] = new int[9];
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][0] = 4;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][1] = savedI_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][2] = savedJ_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][3] = savedK_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][4] = savedL_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][5] = savedM_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][6] = savedN_;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][7] = i;
					_props.heightMapToSectors[dispRawGlob_ + dispTileStart + j + dispRawLocal_][8] = j;
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
			grandChilds_->push_back(new QuadTree(_props.sectors[i]));
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
				for(int k = 0; k < childTree->childs.size();k++)
					D3dRender::getInstance().addQuadTreeModel(&childTree->childs[k]->max, &childTree->childs[k]->center);

				childs_->push_back(childTree);
			}
			if(rawSize_ % 2)rawSize_ = rawSize_ / 2 + 1;
			else rawSize_ /= 2;
		} while(childs_->size() > 4);

		for(int i = 0; i < childs_->size(); i++)
		{
			D3dRender::getInstance().addQuadTreeModel(&childs_[0][i]->max, &childs_[0][i]->center);
			_quadTree->childs.push_back(childs_[0][i]);
		}
		_quadTree->findMaxMinFromChilds();
		D3dRender::getInstance().addQuadTreeModel(&_quadTree->max, &_quadTree->center);
		// assemble quadTree!
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
	int RedactorTerrainManager::pick(precomputeRay* pickRay)
	{
		vector<QuadTree*> intersected_;
		intersected_.push_back(_quadTree);

		vector<QuadTree*> realIntersected_;
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
					realIntersected_.push_back(intersected_[0]);
					intersected_.erase(intersected_.begin());
				}
			}
			else 
				intersected_.erase(intersected_.begin());
		}

		// по расстоянию до камеры! сортировать
		//quick_sort(&realIntersected_, 0, realIntersected_.size() - 1);

		switch(_workType)
		{
			case 1:
			{
				int retValue_ = -1; int terrainId_ = -1;
				for(int i = 0; i < realIntersected_.size(); i++)
				{
					if(getQuadIntersectID(realIntersected_[i]->terrainSector, &pickRay->direction, &pickRay->origin, &retValue_))
					{
						terrainId_ = realIntersected_[i]->terrainSector->terrainId;
						break;
					}
				}
				if(retValue_ == -1) return retValue_;
				_heightmapWork(terrainId_, retValue_);  return terrainId_;
			}
			case 2:
			{
				int terrainId_ = -1;
				float tu; float tv;
				for(int i = 0; i < realIntersected_.size(); i++)
				{
					if(getQuadIntersectID(realIntersected_[i]->terrainSector, &pickRay->direction, &pickRay->origin, &tu, &tv))
					{
						terrainId_ = realIntersected_[i]->terrainSector->terrainId;
						break;
					}
				}
				if(terrainId_ == -1) return terrainId_;
				_textureWork(terrainId_, float2(tu, tv));  return terrainId_;
			}
			default: return -2;
		}
	}
	void RedactorTerrainManager::setWorkType(int type)
	{
		switch(type)
		{ 
		case 0:_workType = TWT_NONE; break;
		case 1:_workType = TWT_HEIGHT; break;
		case 2:_workType = TWT_TEXTURE; break;
		default: _workType = TWT_NONE; break;
		}
	}
	void RedactorTerrainManager::_heightmapWork(int terrainId, int vertId)
	{

	}
	void RedactorTerrainManager::_textureWork(int terrainId, float2 texcoord)
	{

	}
	bool RedactorTerrainManager::generate(int gridX, int gridY)
	{
		_props = Properties(gridX, gridY);
		_generateGeometry();

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
	void RedactorTerrainManager::smoothVert(int id)
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
		float smoothKoeff = ((float)(rand() % 5 + 3))/10.0f;
		_props.heightMap[id].y = (all_height / (float)count)*smoothKoeff + Main_height*(1.0f - smoothKoeff);
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

		for(int i = 0; i < _props.numTiles; i++)
		{
			for(int j = 0; j < _props.numTileVerts; j++)
			{
				int randBiomIndex_ = rand() % _bioms.size();
				float height_ = (float)((rand() % ((int)_bioms[randBiomIndex_].range*diapazon)) - _bioms[randBiomIndex_].halfRange*diapazon);
				_props.heightMap[_props.pickToHeightMap[i][j]].y += _bioms[randBiomIndex_].height + height_;
			}
		}
		_quadTree->update();
		/*
		for(int i = 0; i < _props.numVertsInCol; i++)
		{
			for(int j = 0; j < _props.numVertsInRaw; j++)
			{
				float height = (float)((rand() % (diapazon + 1)) - diapazon_half);
				_props.heightMap[i * _props.numVertsInRaw + j].y += height;
			}
		}*/
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
		int nvir = _props.numVertsInRaw;
		for(int rep = 0; rep < blurHard; rep++)
		{
			for(int i = 0; i < _props.numVertsInCol; i++)
			{
				for(int j = 0; j < _props.numVertsInRaw; j++)
					smoothVert(i*_props.numVertsInRaw + j);
			}
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
		bool RedactorTerrainManager::getQuadIntersectID(TerrainSector* sector, float3* pickDir, float3* pickOrig, int* returnedID)
		{
			int countIntersections = 0;
			float* connections = NULL;	int* connectionsID = NULL;
			int* tempID = NULL;	float* temp = NULL;

			XMFLOAT3** vs = new XMFLOAT3*[3];
			for(int i = 0; i < _props.numSectorQuads; i++)
			{
				vs[0] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 0]]];
				vs[1] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 1]]];
				vs[2] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 2]]];
				if(_intersectTriangle(pickOrig, pickDir, vs))
				{
					tempID = connectionsID;
					connectionsID = new int[countIntersections + 1];
					for(int i = 0; i<countIntersections; i++)
						connectionsID[i] = tempID[i];
					connectionsID[countIntersections] = i;

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
				vs[1] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 1]]];
				vs[2] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 2]]];
				vs[0] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 4]]];
				if(_intersectTriangle(pickOrig, pickDir, vs))
				{
					tempID = connectionsID;
					connectionsID = new int[countIntersections + 1];
					for(int i = 0; i<countIntersections; i++)
						connectionsID[i] = tempID[i];
					connectionsID[countIntersections] = i;

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
			returnedID[0] = _props.quadVertConnect[idd];
			return	true;
		}
		bool RedactorTerrainManager::getQuadIntersectID(TerrainSector* sector, float3* pickDir, float3* pickOrig, float* tu, float* tv)
		{
			float u; float v;
			int countIntersections = 0;
			float2* all_tutv = NULL;	float2* temp_tutv = NULL;
			float* connections = NULL;	float* temp = NULL;
			float3** vs = new float3*[3];

			for(int i = 0; i < _props.numSectorQuads; i++)
			{
				vs[0] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 0]]];//Verts[id][indices[6 * i + 0]];
				vs[1] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 1]]];
				vs[2] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 2]]];
				if(_intersectTriangle(pickOrig, pickDir, vs, &v, &u))
				{
					float raw = i / _props.numQuad;
					float col = i % _props.numQuad;
					u = u / (float)_props.numQuad + raw / (float)_props.numQuad;
					v = v / (float)_props.numQuad + col / (float)_props.numQuad;

					temp_tutv = all_tutv;
					all_tutv = new XMFLOAT2[countIntersections + 1];
					for(int i = 0; i<countIntersections; i++)
						all_tutv[i] = temp_tutv[i];
					all_tutv[countIntersections] = XMFLOAT2(u, v);

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
				vs[1] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 1]]];
				vs[2] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 2]]];
				vs[0] = &_props.heightMap[_props.pickToHeightMap[sector->terrainId][_props.indexes[6 * _props.sectorsToHeightMap[sector->id][i] + 4]]];
				if(_intersectTriangle(pickOrig, pickDir, vs, &v, &u))
				{
					float raw = i / _props.numQuad;
					float col = i % _props.numQuad;
					u = (1.0f - u) / (float)_props.numQuad + raw / (float)_props.numQuad;
					v = (1.0f - v) / (float)_props.numQuad + col / (float)_props.numQuad;

					temp_tutv = all_tutv;
					all_tutv = new XMFLOAT2[countIntersections + 1];
					for(int i = 0; i<countIntersections; i++)
						all_tutv[i] = temp_tutv[i];
					all_tutv[countIntersections] = XMFLOAT2(u, v);

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