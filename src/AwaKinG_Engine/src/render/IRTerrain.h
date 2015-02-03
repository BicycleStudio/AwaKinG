#pragma once
#include <vector>
#include <map>
#include <string>
#include <d3d11.h>
#include "../../../../include/D3DX11.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "Model.h"

using namespace DirectX;
using namespace std;

#pragma comment(lib, "../../lib/x86/D3DX11.lib")

#define checkResult(hres, msg) if(FAILED(hres)){ErrorMessage = msg;return false; }
#define safeRelease(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}

class IRTerrain
{
public:
	virtual bool createBuffer(D3D11_BUFFER_DESC* bd, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buff){ return false; };
	virtual bool createTexture(string fileName, ID3D11ShaderResourceView** texture){ return false; }
	virtual void setTerrainModels(ID3D11Buffer** vertexBuffers, ID3D11ShaderResourceView** textures, int count, ID3D11Buffer* indexBuffer, int indexCount){}
};

