#include "TerrainManager.h"

TerrainManager::TerrainManager()
{
	_iRender = &D3dRender::getInstance();
	_indexBuffer = NULL;
}
void TerrainManager::shutdown()
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
bool TerrainManager::generate(int gridX, int gridY)
{
	_props = Properties(gridX, gridY);

	D3D11_BUFFER_DESC bd_;
	ZeroMemory(&bd_, sizeof(bd_));
	bd_.Usage = D3D11_USAGE_DYNAMIC;
	bd_.ByteWidth = sizeof(Vertex::Simple) * TILE_VERT_NUM * TILE_VERT_NUM;
	bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA initData_;

	_vertexBuffers = new ID3D11Buffer*[_props.NumTiles];
	float texs = (float)1.0f / (float)_props.NumQuad;
	int ter_ind = 0;
	Vertex::Simple* verts = new Vertex::Simple[_props.NumTileVerts];
	for(int ter_ind_x = 0; ter_ind_x < gridX; ter_ind_x++)
	{
		for(int ter_ind_y = 0; ter_ind_y < gridY; ter_ind_y++)
		{
			int number = 0;
			for(int i = 0; i < TILE_VERT_NUM; i++)
			{
				for(int j = 0; j < TILE_VERT_NUM; j++)
				{
					verts[number] = Vertex::Simple(_props.HeightMap[_props.PickToHeightMapMAP[ter_ind][number]], 
						XMFLOAT2(texs * (float)j, texs * (float)i), _props.NormalMap[_props.PickToHeightMapMAP[ter_ind][number]]);
					number++;
				}
			}
			ZeroMemory(&initData_, sizeof(initData_));
			initData_.pSysMem = verts;

			if(!_iRender->createBuffer(&bd_, &initData_, &_vertexBuffers[ter_ind])) { ErrorMessage = "Creation of vertex buffer for terrain"; return false; }
			ter_ind++;
		}
	}
	unsigned int* indexs_ = new unsigned int[_props.NumIndex];
	unsigned int index = 0;
	for(int i = 0; i < _props.NumQuad; i++)
	{
		for(int j = 0; j < _props.NumQuad; j++)
		{
			indexs_[index] = (unsigned int)(i * TILE_VERT_NUM + j);
			indexs_[index + 1] = (unsigned int)(i * TILE_VERT_NUM + j + 1);
			indexs_[index + 2] = (unsigned int)((i + 1) * TILE_VERT_NUM + j);

			indexs_[index + 3] = (unsigned int)(i * TILE_VERT_NUM + j + 1);
			indexs_[index + 4] = (unsigned int)((i + 1) * TILE_VERT_NUM + j + 1);
			indexs_[index + 5] = (unsigned int)((i + 1) * TILE_VERT_NUM + j);

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
	if(!_iRender->createBuffer(&bd_, &initData_, &_indexBuffer)) { ErrorMessage = "Creation of index buffer for terrain"; return false; }

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
		_iRender->createTexture("media/_2048.dds", &ili_, &_textures[i]);

	_iRender->setTerrainModels(_vertexBuffers, _textures, _props.NumTiles, _indexBuffer, _props.NumIndex);
	return true;
}
void TerrainManager::smoothVert(int id)
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
	_props.HeightMap[id].y = (all_height / (float)count)*smoothKoeff + Main_height*(1.0 - smoothKoeff);
}
void TerrainManager::updateVertexBuffer(int idTerrain)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource_;
	_iRender->mapResource(_vertexBuffers[idTerrain], &mappedResource_, D3D11_MAP_WRITE_NO_OVERWRITE);
	auto pData = reinterpret_cast<Vertex::Simple*>(mappedResource_.pData);
	for(int i = 0; i < _props.NumTileVerts; i++)
	{
		pData[i].position = _props.HeightMap[_props.PickToHeightMapMAP[idTerrain][i]];
		pData[i].normal = _props.NormalMap[_props.PickToHeightMapMAP[idTerrain][i]];
	}
	_iRender->unmapResource(_vertexBuffers[idTerrain]);
}
void TerrainManager::randomize(int diapazon)
{
	int diapazon_half = diapazon / 2;
	for(int i = 0; i < _props.NumVertsInRaw; i++)
	{
		for(int j = 0; j < _props.NumVertsInCol; j++)
		{
			float height = (float)((rand() % (diapazon + 1)) - diapazon_half);
			_props.HeightMap[i * _props.NumVertsInRaw + j].y += height;
		}
	}
	normalizeNormals();
	for(int i = 0; i < _props.NumTiles; i++)
		updateVertexBuffer(i);
}
void TerrainManager::normalizeNormals()
{
	for(int i = 0; i < _props.NumVertsInRaw; i++)
	{
		for(int j = 0; j < _props.NumVertsInCol; j++)
		{
			int id = i * _props.NumVertsInRaw + j;
			if(((id) / _props.NumVertsInRaw == (id + 1) / _props.NumVertsInRaw)
				&& ((id + _props.NumVertsInRaw) < _props.MaxId))
			{
				XMVECTOR AB = XMVectorSubtract(XMLoadFloat3(&_props.HeightMap[id + 1]), XMLoadFloat3(&_props.HeightMap[id]));
				XMVECTOR AC = XMVectorSubtract(XMLoadFloat3(&_props.HeightMap[id + _props.NumVertsInRaw]), XMLoadFloat3(&_props.HeightMap[id]));

				XMStoreFloat3(&_props.NormalMap[id], XMVector3Normalize(XMVector3Cross(AB, AC)));
			}
		}
	}
}
void TerrainManager::blurHeightmap(int blurHard)
{
	int nvir = _props.NumVertsInRaw;
	for(int rep = 0; rep < blurHard; rep++)
	{
		for(int i = 0; i < _props.NumVertsInRaw; i++)
		{
			for(int j = 0; j < _props.NumVertsInCol; j++)
				smoothVert(i*_props.NumVertsInRaw + j);
		}
	}
	normalizeNormals();
	for(int i = 0; i < _props.NumTiles; i++)
		updateVertexBuffer(i);
}