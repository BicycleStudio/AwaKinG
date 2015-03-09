#ifndef __RENDER_H
#define __RENDER_H

#include "../ErrorDefines.h"
#include "Model.h"
#include "Camera.h"
#include "../core/map/Map.h"
using namespace Shader;

#define NUM_RENDER_TECHNIQUES 1

class Render {
public:
  void update();
	void shutdown();
  void clear();
	bool resizeBuffer(int sizeX, int sizeY);

  bool createBuffer(D3D11_BUFFER_DESC* bd, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buff);
  bool createTexture(string fileName, ID3D11ShaderResourceView** texture);
  bool createTexture(string fileName, D3DX11_IMAGE_LOAD_INFO* ili, ID3D11ShaderResourceView** texture);
  bool addModel(string modelName, XMFLOAT4X4* worldMatrix);

	string errorMessage;
	bool initialize(HWND hwnd, int sizeX, int sizeY);
  bool createTestTri(XMFLOAT4X4* worldMatrix);

	static Render& getInstance()  {
		static Render render_;
		return render_;
	}
private:
	Render();
	Render(const Render&);

	void _beginScene();
	void _prepareToRenderTechnique(Technique tech);
	void _endScene();

	void _renderTextureMapModel(Model* model, vector<XMFLOAT4X4*>* matrixs);
	bool _initializeShaders();
	bool _initializeRasterizerStates();
	bool _initializeSamplerStates();
	bool _compileShaderFromFile(LPCSTR file, const D3D_SHADER_MACRO* pDefs, LPCSTR szEntry, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob** ppBlobOut);
	void _mapViewProjectionBufferResource();
	void _mapConstantBufferResource(ID3D11Buffer** buffer, XMFLOAT4X4* matrix);
  void _addNewModel(ModelRenderTechnique tech, Model* model, XMFLOAT4X4* worldMatrix);
  void _addModel(ModelRenderTechnique tech, int modelIndex, XMFLOAT4X4* worldMatrix);

#pragma region private vars
	SystemConfiguration _config;
	#pragma region shader vars
		RasterizerState				_rasterizerStates;
		SamplerState					_samplerStates;
		TechniqueBuffers			_textureMap;
		ID3D11Buffer*					_bufferViewProj;
	#pragma endregion

	#pragma region d3d main vars
		private:
			ID3D11Device*           _device;
			ID3D11DeviceContext*    _immediateContext;
			IDXGISwapChain*         _swapChain;
			ID3D11RenderTargetView* _renderTargetView;
			ID3D11Texture2D*				_backBuffer;
			ID3D11DepthStencilView* _depthStencilView;
			ID3D11Texture2D*        _depthStencil;

			D3D_FEATURE_LEVEL       _featureLevel;
			D3D_DRIVER_TYPE         _driverType;
			XMMATRIX								_perspectiveMatrix;
	#pragma endregion
	#pragma region main vars
		private:
      vector<Model*>								_models[NUM_RENDER_TECHNIQUES];
      vector<vector<XMFLOAT4X4*>>		_worldMatrix[NUM_RENDER_TECHNIQUES];
			int														_sizeX;
			int														_sizeY;
			float*												_sceneColor;
#pragma endregion
#pragma endregion
};

#endif // __RENDER_H 