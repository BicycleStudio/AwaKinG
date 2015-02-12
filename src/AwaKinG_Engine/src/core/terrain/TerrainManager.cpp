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

		int4 inStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeIn() - 1);
		int4 outStruct_ = _getLRUD(vertId, currentRaw_, _heightPen->getSizeOut() - 1);
		int penOut_ = (outStruct_.z + 1) * (outStruct_.w + 1);
		int penIn_ = (inStruct_.z + 1) * (inStruct_.w + 1);

		int* temp_ = 0;		int* TerarainIDs_ = 0; int* SectorsIDs_ = 0;
		int countTerrainsToUpdate_ = 0;	int countSectorsToUpdate_ = 0;
		int rawDisp_ = 0;

		for(int i = 0; i < penOut_; i++)
		{
			if(i != 0 && i % (outStruct_.z + 1) == 0)
				rawDisp_ += _props.numVertsInRaw - (outStruct_.z + 1);
			_props.heightMap[outStruct_.x + i + rawDisp_].y += _heightPen->hard;
			#pragma region TerrainIDs update
				int counter_ = 0;
				for(int q = 0; q < _props.heightMapToTerrain[outStruct_.x + i + rawDisp_][0]; q++)
				{
					_vertsToUpdate[_props.heightMapToTerrain[outStruct_.x + i + rawDisp_][counter_ + 1]][_countVertToUpdate[_props.heightMapToTerrain[outStruct_.x + i + rawDisp_][counter_ + 1]]] = _props.heightMapToTerrain[outStruct_.x + i + rawDisp_][counter_ + 2];
					_countVertToUpdate[_props.heightMapToTerrain[outStruct_.x + i + rawDisp_][counter_ + 1]]++;
					bool add_ = true;
					for(int tt = 0; tt<countTerrainsToUpdate_; tt++)
					{
						if(TerarainIDs_[tt] == _props.heightMapToTerrain[outStruct_.x + i + rawDisp_][counter_ + 1])
						{
							add_ = false;
							break;
						}
					}
					if(add_)
					{
						temp_ = TerarainIDs_;			TerarainIDs_ = new int[countTerrainsToUpdate_ + 1];
						for(int tt = 0; tt<countTerrainsToUpdate_; tt++)			TerarainIDs_[tt] = temp_[tt];
						TerarainIDs_[countTerrainsToUpdate_] = _props.heightMapToTerrain[outStruct_.x + i + rawDisp_][counter_ + 1];
						countTerrainsToUpdate_++;
					}
					counter_ += 2;
				}
			#pragma endregion
				
			#pragma region TerrainSectors update
				counter_ = 0;
				for(int q = 0; q < _props.heightMapToSectors[outStruct_.x + i + rawDisp_][0]; q++)
				{
					bool add_ = true;
					for(int tt = 0; tt<countSectorsToUpdate_; tt++)
					{
						if(SectorsIDs_[tt] == _props.heightMapToSectors[outStruct_.x + i + rawDisp_][counter_ + 1])
						{
							add_ = false;
							break;
						}
					}
					if(add_)
					{
						temp_ = SectorsIDs_;			SectorsIDs_ = new int[countSectorsToUpdate_ + 1];
						for(int tt = 0; tt<countSectorsToUpdate_; tt++)			SectorsIDs_[tt] = temp_[tt];
						SectorsIDs_[countSectorsToUpdate_] = _props.heightMapToSectors[outStruct_.x + i + rawDisp_][counter_ + 1];
						countSectorsToUpdate_++;
					}
					counter_ += 2;
				}
			#pragma endregion
			
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
			_props.heightMap[inStruct_.x + i + rawDisp_].y +=_heightPen->hard;
			_heightPen->vertsIn_x[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].x;
			_heightPen->vertsIn_y[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].y;
			_heightPen->vertsIn_z[i] = &_props.heightMap[inStruct_.x + i + rawDisp_].z;
		}
		_heightPen->countDrawSizeIn = penIn_;

		_heightPen->update();

		for(int i = 0; i < countSectorsToUpdate_; i++)			_updateSector(SectorsIDs_[i]);
		for(int i = 0; i < countTerrainsToUpdate_; i++)			_updateSubVertexBuffer(TerarainIDs_[i]);

		delete SectorsIDs_; SectorsIDs_ = 0;
		delete TerarainIDs_; TerarainIDs_ = 0;
		delete temp_; temp_ = 0;
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
		float smoothKoeff = ((float)(rand() % 5 + 3))/10.0f;
		_props.heightMap[id].y = (all_height / (float)count)*smoothKoeff + Main_height*(1.0f - smoothKoeff);
	}
	void RedactorTerrainManager::_updateSubVertexBuffer(int idTerrain)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource_;
		D3dRender::getInstance().mapResource(_vertexBuffers[idTerrain], &mappedResource_, D3D11_MAP_WRITE_NO_OVERWRITE);

		auto pData = reinterpret_cast<Vertex::Simple*>(mappedResource_.pData);
		for(int i = 0; i < _countVertToUpdate[idTerrain]; i++)
			pData[_vertsToUpdate[idTerrain][i]].position.y = _props.heightMap[_props.pickToHeightMap[idTerrain][_vertsToUpdate[idTerrain][i]]].y;
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