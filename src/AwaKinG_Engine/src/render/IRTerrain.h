#pragma once
#include <vector>
#include <map>
#include <string>
//#include <d3d11.h>
#include "../../../../include/D3DX11.h"
#include "../../../../include/d3dcompiler.h"
//#include <d3dcompiler.h>
//#include <DirectXMath.h>
//d3d11.lib
//d3dcompiler.lib
//dxguid.lib
#include "Model.h"

//using namespace DirectX;
using namespace std;

#pragma comment(lib, "../../lib/x86/D3DX11.lib")
#pragma comment(lib, "../../lib/x86/D3D11.lib")

#define checkResult(hres, msg) if(FAILED(hres)){ErrorMessage = msg;return false; }
#define safeRelease(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}
struct int2
{
	int2(){}
	int2(int x_, int y_){ x = x_; y = y_; }
	int x;
	int y;
};
struct int3 : int2
{
	int3(){}
	int3(int x_, int y_, int z_){ x = x_; y = y_; z = z_; }

	int z;
};
class IRTerrain
{
public:
};

