#pragma once
#include "IRTerrain.h"
#include "../core/camera/Camera.h"


class D3dRender : public IRTerrain
{
public:
	enum AwaKinGModelTechnique { AMT_COLORMAP = 0, AMT_TEXTUREMAP = 1, AMT_BUMPMAP = 2 };
	enum SystemModelType { SMT_QUADTREE = 0, SMT_TERRAINPEN = 1 };
#pragma region structs
	struct SystemConfiguration
	{
		SystemConfiguration(){}
		const float Zfar = 100000.0f;
		const float Znear = 0.01f;
	}; SystemConfiguration _config;
	struct RasterizerState
	{
		ID3D11RasterizerState* Solid;
		ID3D11RasterizerState* NonCull;
		ID3D11RasterizerState* Wireframe;
	};
	struct ConstantBufferMatrix
	{
		XMFLOAT4X4 matr;
	};
	struct TechniqueVP
	{
		ID3D11VertexShader* VS;
		ID3D11PixelShader* PS;
		ID3D11InputLayout* IL;
		unsigned int VertexStride;
	};
	struct TechniqueVP_Buf : TechniqueVP
	{
		vector<ID3D11Buffer*>	Buffer;
		vector<int>	IndexOfBuffer;
	};
#pragma endregion
#pragma region singleton
public:
	std::string ErrorMessage;
	static D3dRender& getInstance()
	{
		static D3dRender render;
		return render;
	};
private:
	D3dRender();
	D3dRender(const D3dRender&);
#pragma endregion

#pragma region public functions
public:
	//Before initialize() call setInitialize(HWND hwnd, int sizeX, int sizeY)
	bool initialize();
	void setInitialize(HWND hwnd, int sizeX, int sizeY, string shaderPath);
	void render();
	void shutdown();
	bool resizeBuffer(int sizeX, int sizeY);

	precomputeRay* getPickingRay(int x, int y);

	bool needToInitializeModel(string fileName, int* indexTechnique, int* index);
	XMFLOAT4X4* addModelMatrix(int indexTechnique, int index);
	XMFLOAT4X4* addTextureModel(TextureModel* model);
	bool createBuffer(D3D11_BUFFER_DESC* bd, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buff);
	bool createTexture(string fileName, ID3D11ShaderResourceView** texture);
	bool createTexture(string fileName, D3DX11_IMAGE_LOAD_INFO* ili, ID3D11ShaderResourceView** texture);
	void setRasterizerState(int stateType);

	#pragma region for terrain
	void setVisibleTerrainQuadTree(bool set);
	void setTerrainWireframe(bool set);
	void clearQuadTreeMatrixVector();
	void addQuadTreeModel(float3* max, float3* center);
	void saveResourceToFile(string fileName, ID3D11Resource* resource);
	void unmapResource(ID3D11Buffer* buf);
	void mapResource(ID3D11Buffer* buf, D3D11_MAPPED_SUBRESOURCE* mappedSubResource, D3D11_MAP mapType);
	void setTerrainModels(ID3D11Buffer** vertexBuffers, ID3D11ShaderResourceView** textures, int count, ID3D11Buffer* indexBuffer, int indexCount);
	#pragma endregion
#pragma endregion
#pragma region private functions
private:
	void _beginScene();
	void _prepareToRenderTechnique(TechniqueVP tech);
	void _renderTerrainTile(Model* model);
	void _renderTextureMapModel(ModelEx* model, vector<XMFLOAT4X4*>* matrixs);
	void _renderColorMapModel(ModelEx* model, vector<XMFLOAT4X4*>* matrixs);
	void _endScene();
	bool _initializeShaders();
	bool _compileShaderFromFile(LPCSTR file, const D3D_SHADER_MACRO* pDefs,	LPCSTR szEntry, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob** ppBlobOut);
	void _mapConstantBufferResource(ID3D11Buffer** buffer, XMFLOAT4X4* matrix);
	void _mapConstantBufferResource(ID3D11Buffer** buffer, XMFLOAT4* vector);
	void _mapViewProjectionBufferResource();
	void _createSystemBox();
#pragma endregion

#pragma region private vars
	vector<vector<vector<XMFLOAT4X4*>>>		_worldMatrixs;
	vector<vector<ModelEx*>>							_models;
	vector<Model*>												_terrainTiles;
	ID3D11Buffer*													_terrainTileIndexBuffer;
	bool																	_renderTerrainQuadTree;
	bool																	_renderTerrainWireframe;
	 
	#pragma region shader vars 
		string									_shaderPath;
		TechniqueVP_Buf					_textureMap;
		TechniqueVP_Buf					_colorMap;
		TechniqueVP							_terrainTech;

		ID3D11Buffer*           _bViewProj;
		ConstantBufferMatrix		_cbViewProj;
		ID3D11SamplerState*     _ssLinear;
		RasterizerState					_rs;
		ID3D11SamplerState*			_ssDefault;
	#pragma endregion
	#pragma region d3d main vars
	private:
		ID3D11Device*           _device;
		ID3D11DeviceContext*    _immediateContext;
		IDXGISwapChain*         _swapChain;
		ID3D11RenderTargetView* _renderTargetView;
		ID3D11Texture2D*				_backBuffer;
		ID3D11Texture2D*        _depthStencil;
		ID3D11DepthStencilView* _depthStencilView;

		D3D_FEATURE_LEVEL       _featureLevel;
		D3D_DRIVER_TYPE         _driverType;

		XMFLOAT4X4							_perspectiveMatrix;
		XMMATRIX								_PerspectiveMatrix;
		XMMATRIX								_OrthograficMatrix;
	#pragma endregion
	#pragma region main vars
	private:
		bool										_mayInitialized;
		HWND										_hwnd;
		int											_sizeX;
		int											_sizeY;
		float*									_sceneColor;
		float*									_pickColor;
	#pragma endregion
#pragma endregion
};

