#pragma once
#include "../Parser.h"
#include "../../render/D3dRender.h"

#define TILE_VERT_NUM 64
#define TILE_CELL_SPACE 20.0f 


class TerrainManager
{
#pragma region singleton
public:
	std::string ErrorMessage;
	static TerrainManager& getInstance()
	{
		static TerrainManager engine;
		return engine;
	};

private:
	TerrainManager();
	TerrainManager(const TerrainManager&);
#pragma endregion
void smoothVert(int id);
void updateVertexBuffer(int idTerrain);

#pragma region public functions
public:
	bool generate(int gridX, int gridY);
	void shutdown();
	void randomize(int diapazon);
	void normalizeNormals();
	void blurHeightmap(int blurHard);
#pragma endregion
private:
	struct Properties
	{
		Properties(){}
		Properties(int x, int y)
		{
			NumQuad = (TILE_VERT_NUM - 1);
			NumIndex = NumQuad * NumQuad * 2 * 3;
			SizeX = x;
			SizeY = y;
			NumTiles = SizeX * SizeY;
			PickToHeightMapMAP = new int*[NumTiles];
			NumVertsInRaw = x * NumQuad + 1;
			NumVertsInCol = y * NumQuad + 1;
			NumTileQuads = NumQuad * NumQuad;
			NumTileVerts = TILE_VERT_NUM * TILE_VERT_NUM;
			MaxId = NumVertsInRaw * NumVertsInCol;
			HeightMapToTerrainMAP = new int*[MaxId];
			QuadVertConnect = new int[NumTileQuads];
			int k = 0;
			for(int i = 0; i < NumTileQuads; i++)
			{
				if(i != 0 && i % NumQuad == 0)
					k += 1;
				QuadVertConnect[i] = i + k;
			}
			for(int i = 0; i < MaxId; i++)
			{
				HeightMapToTerrainMAP[i] = new int[1];
				HeightMapToTerrainMAP[i][0] = 0;
			}
			for(int i = 0; i < NumTiles; i++)
				PickToHeightMapMAP[i] = new int[NumTileVerts];
			
			k = 0;
			int k_raw = 0;
			for(int i = 0; i < NumTiles; i++)
			{
				k_raw = 0;
				int qwer = i % SizeX;
				if(qwer == 0 && i != 0)
					k += NumVertsInRaw * NumQuad;
				else
					qwer *= NumQuad;

				int savedI_ = 0;int savedJ_ = 0;int savedK_ = 0;int savedL_ = 0;int savedM_ = 0;int savedN_ = 0;
				for(int j = 0; j < NumTileVerts; j++)
				{
					if(j % TILE_VERT_NUM == 0 && j != 0)
						k_raw += NumVertsInRaw - TILE_VERT_NUM;
					PickToHeightMapMAP[i][j] = k + qwer + j + k_raw;

					switch(HeightMapToTerrainMAP[k + qwer + j + k_raw][0])
					{
					case 0:
						HeightMapToTerrainMAP[k + qwer + j + k_raw] = new int[3];
						HeightMapToTerrainMAP[k + qwer + j + k_raw][0] = 1;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][1] = i;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][2] = j;
						break;
					case 1:
						savedI_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][1];
						savedJ_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][2];

						HeightMapToTerrainMAP[k + qwer + j + k_raw] = new int[5];
						HeightMapToTerrainMAP[k + qwer + j + k_raw][0] = 2;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][1] = savedI_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][2] = savedJ_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][3] = i;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][4] = j;
						break;
					case 2:
						savedI_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][1];
						savedJ_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][2];
						savedK_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][3];
						savedL_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][4];

						HeightMapToTerrainMAP[k + qwer + j + k_raw] = new int[7];
						HeightMapToTerrainMAP[k + qwer + j + k_raw][0] = 3;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][1] = savedI_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][2] = savedJ_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][3] = savedK_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][4] = savedL_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][5] = i;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][6] = j;
						break;
					case 3:
						savedI_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][1];
						savedJ_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][2];
						savedK_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][3];
						savedL_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][4];
						savedM_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][5];
						savedN_ = HeightMapToTerrainMAP[k + qwer + j + k_raw][6];

						HeightMapToTerrainMAP[k + qwer + j + k_raw] = new int[9];
						HeightMapToTerrainMAP[k + qwer + j + k_raw][0] = 4;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][1] = savedI_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][2] = savedJ_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][3] = savedK_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][4] = savedL_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][5] = savedM_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][6] = savedN_;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][7] = i;
						HeightMapToTerrainMAP[k + qwer + j + k_raw][8] = j;
						break;
					}
				}
			}
			float one_shir = ((float)NumQuad) * (float)TILE_CELL_SPACE;
			float pol_width = SizeX * one_shir / 2.0f;
			float pol_height = SizeY * one_shir / 2.0f;
			for(int i = 0; i < NumVertsInCol; i++)
			{
				for(int j = 0; j < NumVertsInRaw; j++)
				{
					HeightMap.push_back(
						XMFLOAT3((float)TILE_CELL_SPACE * i - pol_height, 0.0f, (float)TILE_CELL_SPACE * j - pol_width));
					NormalMap.push_back(XMFLOAT3(0.0f, 1.0f, 0.0f));
				}
			}
		}
		void Release()
		{
			HeightMap.clear(); NormalMap.clear();
			delete[] PickToHeightMapMAP;
			delete[] HeightMapToTerrainMAP;
			delete QuadVertConnect;
		}
		vector<XMFLOAT3> HeightMap;
		vector<XMFLOAT3> NormalMap;
		int** PickToHeightMapMAP;
		int** HeightMapToTerrainMAP;
		int* QuadVertConnect;
		int SizeX; int SizeY;
		int NumVertsInRaw;
		int NumVertsInCol;
		int NumTiles;
		int NumTileVerts;
		int NumTileQuads;
		int MaxId;
		int NumQuad;
		int NumIndex;
		//int* AllIndexes;
	};
	Properties									_props;

	IRTerrain*									_iRender;
	ID3D11Buffer*								_indexBuffer;
	ID3D11Buffer**							_vertexBuffers;
	ID3D11ShaderResourceView**	_textures;
};