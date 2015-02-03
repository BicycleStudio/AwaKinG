#pragma once
#include <vector>
#include <map>
#include <string>
#include <d3d11.h>
#include "../../../../include/D3DX11.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Model.h"

#define checkResult(hres, msg) if(FAILED(hres)){ErrorMessage = msg;return false; }
#define safeRelease(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}

using namespace DirectX;
using namespace std;

#pragma comment(lib, "../../lib/x86/D3DX11.lib")

class D3dRender
{
public:
	enum AwaKinGModelTechnique { AMT_TEXTUREMAP = 0, AMT_BUMPMAP = 1 };
#pragma region structs
	struct SystemConfiguration
	{
		const float Zfar = 100000.0f;
		const float Znear = 0.01f;
	}; SystemConfiguration _config;
	struct RasterizerState
	{
		ID3D11RasterizerState* Solid;
		ID3D11RasterizerState* NonCull;
		ID3D11RasterizerState* Wireframe;
	};
	struct ConstantBuffer
	{
		XMFLOAT4X4 matr;
	};
	struct TechniqueVP
	{
		ID3D11VertexShader* VS;
		ID3D11PixelShader* PS;
		ID3D11InputLayout* IL;
		ID3D11Buffer*	Buffer;
		int	IndexOfBuffer;
		unsigned int VertexStride;
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
	void setInitialize(HWND hwnd, int sizeX, int sizeY);
	void render();
	void shutdown();
	bool resizeBuffer(int sizeX, int sizeY);

	bool needToInitializeModel(string fileName, int* indexTechnique, int* index);
	XMFLOAT4X4* addModelMatrix(int indexTechnique, int index);
	XMFLOAT4X4* addTextureModel(TextureModel* model);
	bool createBuffer(D3D11_BUFFER_DESC* bd, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buff);
	bool createTexture(string fileName, ID3D11ShaderResourceView** texture);
#pragma endregion
#pragma region private functions
private:
	void _beginScene();
	void _prepareToRenderTechnique(TechniqueVP tech);
	void _renderTextureMapModel(Model* model, vector<XMFLOAT4X4>* matrixs);
	void _endScene();
	bool _initializeShaders();
	bool _compileShaderFromFile(LPCWSTR pFileName,	const D3D_SHADER_MACRO* pDefines,
		LPCSTR pEntrypoint, LPCSTR pTarget,	UINT Flags1, UINT Flags2,	ID3DBlob** ppCode);
	void _mapConstantBufferResource(ID3D11Buffer** buffer, XMFLOAT4X4* matrix);
	void _mapViewProjectionBufferResource();
#pragma endregion

#pragma region public vars
public:
	XMFLOAT4X4*								ViewMatrix;
#pragma endregion
#pragma region private vars
	vector<vector<vector<XMFLOAT4X4>>>		_worldMatrixs;
	vector<vector<Model*>>								_models;
	 
	#pragma region vars for picking 
	private:
		D3D11_BOX								_dboxPICK;
		D3D11_TEXTURE2D_DESC		_tex2DDescPICK;
		ID3D11Texture2D*        _backReadFromPICK;
	#pragma endregion
	#pragma region shader vars 
		TechniqueVP							_TextureMap;
	
		ID3D11Buffer*           _bViewProj;
		ConstantBuffer					_cbViewProj;
		ID3D11SamplerState*     _ssLinear;
		RasterizerState					_rs;
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
	#pragma endregion
#pragma endregion
};

