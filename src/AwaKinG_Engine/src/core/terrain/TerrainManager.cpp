#include "TerrainManager.h"


TerrainManager::TerrainManager()
{
	_indexBuffer = NULL;
	_2048Path = "../../media/terrain/_2048.dds";
}
RedactorTerrainManager::RedactorTerrainManager()
{
	_indexBuffer = NULL; _workType = TWT_NONE;
	_2048Path = "../../../../media/terrain/_2048.dds";
}
#pragma region virtual functions
	void TerrainManager::shutdown()
	{
		safeRelease(_indexBuffer);
	}
	void RedactorTerrainManager::shutdown()
	{
		safeRelease(_indexBuffer);
		for(int i = 0; i < _props.NumTiles; i++)
		{
			safeRelease(_vertexBuffers[i]);
			delete _vertexBuffers[i];
		}
		for(int i = 0; i < _props.NumTiles; i++)
		{
			safeRelease(_textures[i]);
			delete _textures[i];
		}
		_props.Release();
	}
	bool TerrainManager::_generateGeometry()
	{
		return true;
	}
	bool RedactorTerrainManager::_generateGeometry()
	{
		D3D11_BUFFER_DESC bd_;
		ZeroMemory(&bd_, sizeof(bd_));
		bd_.Usage = D3D11_USAGE_DYNAMIC;
		bd_.ByteWidth = sizeof(Vertex::Simple) * _props.NumTileVerts;
		bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		D3D11_SUBRESOURCE_DATA initData_;

		_vertexBuffers = new ID3D11Buffer*[_props.NumTiles];
		float texs = (float)1.0f / (float)_props.NumQuad;
		int ter_ind = 0;
		Vertex::Simple* verts = new Vertex::Simple[_props.NumTileVerts];
		for(int ter_ind_x = 0; ter_ind_x < _props.SizeX; ter_ind_x++)
		{
			for(int ter_ind_y = 0; ter_ind_y < _props.SizeY; ter_ind_y++)
			{
				int number = 0;
				for(int i = 0; i < _props.NumVerts; i++)
				{
					for(int j = 0; j < _props.NumVerts; j++)
					{
						verts[number] = Vertex::Simple(_props.HeightMap[_props.PickToHeightMapMAP[ter_ind][number]],
							XMFLOAT2(texs * (float)j, texs * (float)i), _props.NormalMap[_props.PickToHeightMapMAP[ter_ind][number]]);
						number++;
					}
				}
				ZeroMemory(&initData_, sizeof(initData_));
				initData_.pSysMem = verts;
				if(!D3dRender::getInstance().createBuffer(&bd_, &initData_, &_vertexBuffers[ter_ind])) { ErrorMessage = "Creation of vertex buffer for terrain"; return false; }
				ter_ind++;
			}
		}
		unsigned int* indexs_ = new unsigned int[_props.NumIndex];
		unsigned int index = 0;
		for(int i = 0; i < _props.NumQuad; i++)
		{
			for(int j = 0; j < _props.NumQuad; j++)
			{
				indexs_[index] = (unsigned int)(i *  _props.NumVerts + j);
				indexs_[index + 1] = (unsigned int)(i *  _props.NumVerts + j + 1);
				indexs_[index + 2] = (unsigned int)((i + 1) *  _props.NumVerts + j);

				indexs_[index + 3] = (unsigned int)(i *  _props.NumVerts + j + 1);
				indexs_[index + 4] = (unsigned int)((i + 1) *  _props.NumVerts + j + 1);
				indexs_[index + 5] = (unsigned int)((i + 1) *  _props.NumVerts + j);

				index += 6;
			}
		}

		ZeroMemory(&bd_, sizeof(bd_));
		bd_.Usage = D3D11_USAGE_DEFAULT;
		bd_.ByteWidth = sizeof(UINT)* _props.NumIndex;
		bd_.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd_.CPUAccessFlags = 0;
		bd_.MiscFlags = 0;
		ZeroMemory(&initData_, sizeof(initData_));
		initData_.pSysMem = indexs_;
		if(!D3dRender::getInstance().createBuffer(&bd_, &initData_, &_indexBuffer)) { ErrorMessage = "Creation of index buffer for terrain"; return false; }

		return true;
	}
	bool TerrainManager::loadFromFile(string fileName)
	{
		tryOpenStream(fileName, "r");

		int numV_ = 0; float cellSpace_ = 0.0f; int sizeX_ = 0; int sizeY_ = 0;
		tryReadInt(&numV_); tryReadFloat(&cellSpace_);
		tryReadInt(&sizeX_); tryReadInt(&sizeY_);

		int numTiles_ = sizeX_ * sizeY_;
		int numQuad_ = numV_ - 1;
		int numTileVerts_ = numV_ *  numV_;
		int numIndex_ = numQuad_ * numQuad_ * 2 * 3;
		float tileHalf = (cellSpace_*numQuad_) / 2.0f;

		D3D11_BUFFER_DESC bd_;
		ZeroMemory(&bd_, sizeof(bd_));
		bd_.Usage = D3D11_USAGE_DYNAMIC;
		bd_.ByteWidth = sizeof(Vertex::Simple) * numTileVerts_;
		bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd_.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		D3D11_SUBRESOURCE_DATA initData_;

		_vertexBuffers = new ID3D11Buffer*[numTiles_];
		float texs = (float)1.0f / (float)numQuad_;
		int ter_ind = 0;
		Vertex::Simple* verts = new Vertex::Simple[numTileVerts_];

		float totalDisplaceX = sizeX_ * tileHalf;
		float totalDisplaceY = sizeY_ * tileHalf;

		for(int ter_i = 0; ter_i < sizeX_; ter_i++)
		{
			for(int ter_j = 0; ter_j < sizeY_; ter_j++)
			{
				float displaceX_ = tileHalf * ter_i * 2;
				float displaceY_ = tileHalf * ter_j * 2;
				for(int i = 0; i < numV_; i++)
				{
					for(int j = 0; j < numV_; j++)
					{
						verts[i*numV_ + j] = Vertex::Simple(
							XMFLOAT3(cellSpace_ * (float)i + displaceX_ - totalDisplaceX, 0.0f, cellSpace_ * (float)j + displaceY_ - totalDisplaceY),
							XMFLOAT2(texs * (float)j, texs * (float)i));
						tryReadFloat(&verts[i*numV_ + j].position.y);
					}
				}
				ZeroMemory(&initData_, sizeof(initData_));
				initData_.pSysMem = verts;

				if(!D3dRender::getInstance().createBuffer(&bd_, &initData_, &_vertexBuffers[ter_ind])) { ErrorMessage = "Creation of vertex buffer for terrain"; return false; }
				ter_ind++;
			}
		}
		tryCloseStream();

		unsigned int* indexs_ = new unsigned int[numIndex_];
		unsigned int index = 0;
		for(int i = 0; i < numQuad_; i++)
		{
			for(int j = 0; j < numQuad_; j++)
			{
				indexs_[index] = (unsigned int)(i *  numV_ + j);
				indexs_[index + 1] = (unsigned int)(i *  numV_ + j + 1);
				indexs_[index + 2] = (unsigned int)((i + 1) *  numV_ + j);

				indexs_[index + 3] = (unsigned int)(i *  numV_ + j + 1);
				indexs_[index + 4] = (unsigned int)((i + 1) *  numV_ + j + 1);
				indexs_[index + 5] = (unsigned int)((i + 1) *  numV_ + j);

				index += 6;
			}
		}

		ZeroMemory(&bd_, sizeof(bd_));
		bd_.Usage = D3D11_USAGE_DEFAULT;
		bd_.ByteWidth = sizeof(UINT)* numIndex_;
		bd_.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd_.CPUAccessFlags = 0;
		bd_.MiscFlags = 0;
		ZeroMemory(&initData_, sizeof(initData_));
		initData_.pSysMem = indexs_;
		if(!D3dRender::getInstance().createBuffer(&bd_, &initData_, &_indexBuffer)) { ErrorMessage = "Creation of index buffer for terrain"; return false; }
		
		_textures = new ID3D11ShaderResourceView*[numTiles_];

		string textureFName_ = fileName.substr(0, fileName.length() - 4);
		for(int i = 0; i < numTiles_; i++)
		{
			char str[3] = { '_', '_', '_' };
			sprintf_s(str, "%d", i);
			D3dRender::getInstance().createTexture(textureFName_ + str + ".dds", NULL, &_textures[i]);
		}
		D3dRender::getInstance().setTerrainModels(_vertexBuffers, _textures, numTiles_, _indexBuffer, numIndex_);
		return true;
	}
	bool RedactorTerrainManager::loadFromFile(string fileName)
	{
		tryOpenStream(fileName, "r");

		int numV_ = 0; float cellSpace_ = 0.0f; int sizeX_ = 0; int sizeY_ = 0;
		tryReadInt(&numV_); tryReadFloat(&cellSpace_);
		tryReadInt(&sizeX_); tryReadInt(&sizeY_);

		_props.Release();
		_props = Properties(sizeX_, sizeY_, numV_, cellSpace_);

		for(int ter_i = 0; ter_i < _props.SizeX; ter_i++)
		{
			for(int ter_j = 0; ter_j < _props.SizeY; ter_j++)
			{
				for(int i = 0; i < _props.NumVerts; i++)
				{
					for(int j = 0; j < _props.NumVerts; j++)
					{
						tryReadFloat(&_props.HeightMap[_props.PickToHeightMapMAP[ter_i*_props.SizeX + ter_j][i*_props.NumVerts + j]].y);
					}
				}
			}
		}
		tryCloseStream();

		if(!_generateGeometry())
			return false;

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

		_textures = new ID3D11ShaderResourceView*[_props.NumTiles];

		string textureFName_ = fileName.substr(0, fileName.length() - 4);
		for(int i = 0; i < _props.NumTiles; i++)
		{
			char str[3] = { '_', '_', '_' };
			sprintf_s(str, "%d", i);
			D3dRender::getInstance().createTexture(textureFName_ + str + ".dds", &ili_, &_textures[i]);
		}

		D3dRender::getInstance().setTerrainModels(_vertexBuffers, _textures, _props.NumTiles, _indexBuffer, _props.NumIndex);

		return true;
	}
#pragma endregion
#pragma region redactor functions
	int RedactorTerrainManager::pick(XMFLOAT3 pickRay)
	{
		int terrainId_ = 0;//getTerrainID(pickRay);
		int vertId_ = 0; XMFLOAT2 texcoord = XMFLOAT2(0.0f, 0.0f);
		switch(_workType)
		{
		case 0:			return terrainId_;
		case 1:	/* getVertId() ?????*/ _heightmapWork(terrainId_, vertId_);  return terrainId_;
		case 2:	/* getVertId&tutv()?*/ _textureWork(terrainId_, vertId_, texcoord);  return terrainId_;
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
	void RedactorTerrainManager::_textureWork(int terrainId, int vertId, XMFLOAT2 texcoord)
	{

	}
	bool RedactorTerrainManager::generate(int gridX, int gridY, int numVerts, float cellSpace)
	{
		_props = Properties(gridX, gridY, numVerts, cellSpace);
		_generateGeometry();

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

		_textures = new ID3D11ShaderResourceView*[_props.NumTiles];
		for(int i = 0; i < _props.NumTiles; i++)
			D3dRender::getInstance().createTexture(_2048Path, &ili_, &_textures[i]);

		D3dRender::getInstance().setTerrainModels(_vertexBuffers, _textures, _props.NumTiles, _indexBuffer, _props.NumIndex);
		return true;
	}
	void RedactorTerrainManager::smoothVert(int id)
	{
		int count = 0;
		float Main_height = _props.HeightMap[id].y;
		float all_height = 0.0f;
		bool left = ((id - 1) / _props.NumVertsInRaw == (id) / _props.NumVertsInRaw) && (id>0);
		bool right = ((id + 1) / _props.NumVertsInRaw == (id) / _props.NumVertsInRaw) && (id < _props.MaxId);
		if(id - _props.NumVertsInRaw > 0)
		{
			all_height += _props.HeightMap[id - _props.NumVertsInRaw].y;
			count++;
			if(left)
			{
				count++;
				all_height += _props.HeightMap[id - _props.NumVertsInRaw - 1].y;
			}
			if(right)
			{
				count++;
				all_height += _props.HeightMap[id - _props.NumVertsInRaw + 1].y;
			}
		}
		if(left)
		{
			count++;
			all_height += _props.HeightMap[id - 1].y;
		}
		if(right)
		{
			count++;
			all_height += _props.HeightMap[id + 1].y;
		}
		if(id + _props.NumVertsInRaw < _props.MaxId)
		{
			all_height += _props.HeightMap[id + _props.NumVertsInRaw].y;
			count++;
			if(left)
			{
				count++;
				all_height += _props.HeightMap[id + _props.NumVertsInRaw - 1].y;
			}
			if(right)
			{
				count++;
				all_height += _props.HeightMap[id + _props.NumVertsInRaw + 1].y;
			}
		}
		float smoothKoeff = ((float)(rand() % 5 + 3))/10.0f;
		_props.HeightMap[id].y = (all_height / (float)count)*smoothKoeff + Main_height*(1.0f - smoothKoeff);
	}
	void RedactorTerrainManager::_updateVertexBuffer(int idTerrain)
	{
		D3D11_MAPPED_SUBRESOURCE mappedResource_;
		D3dRender::getInstance().mapResource(_vertexBuffers[idTerrain], &mappedResource_, D3D11_MAP_WRITE_NO_OVERWRITE);
		auto pData = reinterpret_cast<Vertex::Simple*>(mappedResource_.pData);
		for(int i = 0; i < _props.NumTileVerts; i++)
		{
			pData[i].position = _props.HeightMap[_props.PickToHeightMapMAP[idTerrain][i]];
			pData[i].normal = _props.NormalMap[_props.PickToHeightMapMAP[idTerrain][i]];
		}
		D3dRender::getInstance().unmapResource(_vertexBuffers[idTerrain]);
	}
	void RedactorTerrainManager::randomize(int diapazon)
	{
		int diapazon_half = diapazon / 2;
		for(int i = 0; i < _props.NumVertsInCol; i++)
		{
			for(int j = 0; j < _props.NumVertsInRaw; j++)
			{
				float height = (float)((rand() % (diapazon + 1)) - diapazon_half);
				_props.HeightMap[i * _props.NumVertsInRaw + j].y += height;
			}
		}
		normalizeNormals();
		for(int i = 0; i < _props.NumTiles; i++)
			_updateVertexBuffer(i);
	}
	void RedactorTerrainManager::normalizeNormals()
	{
		for(int i = 0; i < _props.NumVertsInCol; i++)
		{
			for(int j = 0; j < _props.NumVertsInRaw; j++)
			{
				int id = i * _props.NumVertsInCol + j;
				if(((id) / _props.NumVertsInCol == (id + 1) / _props.NumVertsInCol)
					&& ((id + _props.NumVertsInCol) < _props.MaxId))
				{
					XMVECTOR AB = XMVectorSubtract(XMLoadFloat3(&_props.HeightMap[id + 1]), XMLoadFloat3(&_props.HeightMap[id]));
					XMVECTOR AC = XMVectorSubtract(XMLoadFloat3(&_props.HeightMap[id + _props.NumVertsInRaw]), XMLoadFloat3(&_props.HeightMap[id]));

					XMStoreFloat3(&_props.NormalMap[id], XMVector3Normalize(XMVector3Cross(AB, AC)));
				}
			}
		}
	}
	void RedactorTerrainManager::blurHeightmap(int blurHard)
	{
		int nvir = _props.NumVertsInRaw;
		for(int rep = 0; rep < blurHard; rep++)
		{
			for(int i = 0; i < _props.NumVertsInCol; i++)
			{
				for(int j = 0; j < _props.NumVertsInRaw; j++)
					smoothVert(i*_props.NumVertsInRaw + j);
			}
		}
		normalizeNormals();
		for(int i = 0; i < _props.NumTiles; i++)
			_updateVertexBuffer(i);
	}
	bool RedactorTerrainManager::saveToFile(string fileName)
	{
		tryOpenStream(fileName, "w");
		string textureFName_ = fileName.substr(0, fileName.length()-4);

		tryWriteInt(_props.NumVerts); tryWriteFloat(_props.CellSpace);
		Parser::getInstance().newLine();
		tryWriteInt(_props.SizeX); tryWriteInt(_props.SizeY);
		Parser::getInstance().newLine();
		for(int ter_i = 0; ter_i < _props.SizeX; ter_i++)
		{
			for(int ter_j = 0; ter_j < _props.SizeY; ter_j++)
			{
				for(int i = 0; i < _props.NumVerts; i++)
				{
					for(int j = 0; j < _props.NumVerts; j++)
					{
						tryWriteFloat(_props.HeightMap[_props.PickToHeightMapMAP[ter_i*_props.SizeX + ter_j][i*_props.NumVerts + j]].y);
					}
					Parser::getInstance().newLine();
				}
				char str[4] = { '_', '_', '_', '_' };
				sprintf_s(str, "%d", ter_i*_props.SizeX + ter_j);
				ID3D11Resource* ress;		_textures[ter_i*_props.SizeX + ter_j]->GetResource(&ress);
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
#pragma endregion
