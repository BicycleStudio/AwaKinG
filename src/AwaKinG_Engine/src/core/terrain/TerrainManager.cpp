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
	/*
	_countTiles = gridX*gridY;
	float texs = (float)1.0f / (float)(TILE_VERT_NUM - 1);
	Vertex::Simple* verts = new Vertex::Simple[TILE_VERT_NUM*TILE_VERT_NUM];
	unsigned int countAllVerts = (TILE_QUAD_NUM * gridX + 1) *(TILE_QUAD_NUM * gridY + 1);
	_heightMap = new XMFLOAT3[countAllVerts];

	float totalDisplaceX = gridX * TILE_HALF;
	float totalDisplaceY = gridY * TILE_HALF;

	D3D11_BUFFER_DESC bd_;
	ZeroMemory(&bd_, sizeof(bd_));
	bd_.Usage = D3D11_USAGE_DEFAULT;
	bd_.ByteWidth = sizeof(Vertex::Simple) * TILE_VERT_NUM * TILE_VERT_NUM;
	bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA initData_;

	_vertexBuffers = new ID3D11Buffer*[_countTiles];
	int indexforVBuf_ = 0;
	for(int gx = 0; gx < gridX; gx++)
	{
		for(int gy = 0; gy < gridY; gy++)
		{
			int number = 0;
			float displaceX_ = TILE_HALF*gx * 2;
			float displaceY_ = TILE_HALF*gy * 2;

			for(int i = 0; i < TILE_VERT_NUM; i++)
			{
				for(int j = 0; j < TILE_VERT_NUM; j++)
				{
					verts[number] = Vertex::Simple(XMFLOAT3(TILE_CELL_SPACE * (float)i + displaceX_ - totalDisplaceX, 0.0f, TILE_CELL_SPACE * (float)j + displaceY_ - totalDisplaceY),
						XMFLOAT2(texs * (float)j, texs * (float)i), 
						XMFLOAT3(0.0f, 1.0f, 0.0f));
					number++;
				}
			}
			ZeroMemory(&initData_, sizeof(initData_));
			initData_.pSysMem = verts;

			ID3D11Buffer* vBuf_;
			if(!_iRender->createBuffer(&bd_, &initData_, &vBuf_)) { ErrorMessage = "Creation of vertex buffer for terrain"; return false; }
			_vertexBuffers[indexforVBuf_] = vBuf_;
			indexforVBuf_++;
		}
	}

	unsigned int* indexs_ = new unsigned int[TILE_INDEX_NUM];
	unsigned int index = 0;
	for(unsigned int i = 0; i < TILE_QUAD_NUM; i++)
	{
		for(unsigned int j = 0; j < TILE_QUAD_NUM; j++)
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
	bd_.ByteWidth = sizeof(UINT)* TILE_INDEX_NUM;
	bd_.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_.CPUAccessFlags = 0;
	bd_.MiscFlags = 0;
	ZeroMemory(&initData_, sizeof(initData_));
	initData_.pSysMem = indexs_;
	if(!_iRender->createBuffer(&bd_, &initData_, &_indexBuffer)) { ErrorMessage = "Creation of index buffer for terrain"; return false; }
	
	_textures = new ID3D11ShaderResourceView*[_countTiles];

	for(int i = 0; i < _countTiles; i++)
		_textures[i] = 0;
		//_iRender->createTexture(fileName.substr(0, fileName.length() - 3) + "dds", &texture_)

	_iRender->setTerrainModels(_vertexBuffers, _textures, _countTiles, _indexBuffer, TILE_INDEX_NUM);
	//ID3D11ShaderResourceView* texture_;
	//checkRenderResult(_d3dRender);

	return true;
}
bool TerrainManager::generate(int gridX, int gridY)
{*/
	_props = Properties(gridX, gridY);
	//Vertex::Simple* verts = new Vertex::Simple[_props.NumTileVerts];
	//float totalDisplaceX = gridX * TILE_HALF;
	//float totalDisplaceY = gridY * TILE_HALF;

	/*
	VERTS_ID_To_Update = new int[Terrain_Properties.Num_Lands][];
	COUNT_VERTS_ID_To_Update = new int[Terrain_Properties.Num_Lands];
	for(int i = 0; i < Terrain_Properties.Num_Lands; i++)
	{
		COUNT_VERTS_ID_To_Update[i] = 0;
		VERTS_ID_To_Update[i] = new int[11 * 11 * 4];
	}

	Pick_Colors = new Vector4[Terrain_Properties.Num_Lands];
	int coi = 0;
	float xxx = 0.0f;
	while(xxx < 1.0f)
	{
		if(coi == Terrain_Properties.Num_Lands) break;
		float yyy = 0.0f;
		while(yyy < 1.0f)
		{
			if(coi == Terrain_Properties.Num_Lands) break;
			float zzz = 0.0f;
			while(zzz < 1.0f)
			{
				if(coi == Terrain_Properties.Num_Lands) break;
				Pick_Colors[coi] = new Vector4(xxx, yyy, zzz, 1.0f);
				coi++;
				zzz += 0.02f;
			}
			yyy += 0.02f;
		}
		xxx += 0.02f;
	}

	Pen.Initialize(IDmnTerrain.Device, Cell_Space);
	*/
	D3D11_BUFFER_DESC bd_;
	ZeroMemory(&bd_, sizeof(bd_));
	bd_.Usage = D3D11_USAGE_DEFAULT;
	bd_.ByteWidth = sizeof(Vertex::Simple) * TILE_VERT_NUM * TILE_VERT_NUM;
	bd_.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_.CPUAccessFlags = 0;
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


	_textures = new ID3D11ShaderResourceView*[_props.NumTiles];

	for(int i = 0; i < _props.NumTiles; i++)
		_iRender->createTexture("media/_2048.dds", &_textures[i]);
	//_textures[i] = 0;

	_iRender->setTerrainModels(_vertexBuffers, _textures, _props.NumTiles, _indexBuffer, _props.NumIndex);

	return true;
}