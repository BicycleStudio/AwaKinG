#pragma once
#include <string>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

using namespace DirectX;

class D3dRender
{
#pragma region singlton
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
	void setInitialize(HWND hwnd, int sizeX, int sizeY);
	bool initialize();
	void shutdown();
#pragma endregion

#pragma region main vars
private:
	bool										_mayInitialized;
	HWND										_hwnd;
	int											_sizeX;
	int											_sizeY;
	float*									_sceneColor;
#pragma endregion

private:
	D3D11_BOX								_dboxPICK;
	D3D11_TEXTURE2D_DESC		_tex2DDescPICK;
	ID3D11Texture2D*        _backReadFromPICK;

#pragma region shader vars
	struct ConstantBuffer
	{
		XMMATRIX View;
		XMMATRIX Projection;
	};
	ID3D11Buffer*           _bViewProj;
	ConstantBuffer					_cbViewProj;
	ID3D11SamplerState*     _ssLinear;
	ID3D11RasterizerState*	_rsDefault;
	ID3D11RasterizerState*	_rsWireframe;
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
	XMMATRIX*								_ViewMatrix;
#pragma endregion
};

