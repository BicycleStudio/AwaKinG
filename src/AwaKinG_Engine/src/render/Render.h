#ifndef __RENDER_H
#define __RENDER_H

#include <Windows.h>
#include <vector>
#include <string>
#include "../../../../include/d3d11.h"
#include "../../../../include/D3DX11.h"
#include "../../../../include/d3dcompiler.h"
#include "../../../../include/xnamath.h"

using namespace std;

#pragma comment(lib, "../../lib/x86/D3DX11.lib")
#pragma comment(lib, "../../lib/x86/D3D11.lib")

#define CHECK_RESULT(hres, msg) if(FAILED(hres)){ErrorMessage = msg;return false; }
#define SAFE_RELEASE(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}

class Render
{
public:
	void update();
	void shutdown();
	bool resizeBuffer(int sizeX, int sizeY);

	string ErrorMessage;
	bool initialize(HWND hwnd, int sizeX, int sizeY);
	static Render* getInstance()  {
		static Render *render_ = new Render();
		return render_;
	}
private:
	Render();
	Render(const Render&);

	void _beginScene();
	void _endScene();

#pragma region private vars
	struct SystemConfiguration
	{
		SystemConfiguration(){}
		const float Zfar = 100000.0f;
		const float Znear = 0.01f;
	}; SystemConfiguration _config;

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