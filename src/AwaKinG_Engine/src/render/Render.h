#ifndef __RENDER_H
#define __RENDER_H

#include "Additional.h"
using namespace Shader;

class Render
{
public:
	void update();
	void shutdown();
	bool resizeBuffer(int sizeX, int sizeY);

	string errorMessage;
	bool initialize(HWND hwnd, int sizeX, int sizeY);

	static Render* getInstance()  {
		static Render *render_ = new Render();
		return render_;
	}
private:
	Render();
	Render(const Render&);

	void _beginScene();
	void _prepareToRenderTechnique(Technique tech);
	void _endScene();

	void _renderTextureMapModel(/*Model* model,*/ vector<XMFLOAT4X4*>* matrixs);
	bool _initializeShaders();
	bool _initializeRasterizerStates();
	bool _initializeSamplerStates();
	bool _compileShaderFromFile(LPCSTR file, const D3D_SHADER_MACRO* pDefs, LPCSTR szEntry, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob** ppBlobOut);
	void _mapViewProjectionBufferResource();

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
			int											_sizeX;
			int											_sizeY;
			float*									_sceneColor;
	#pragma endregion
#pragma endregion
};

#endif // __RENDER_H 