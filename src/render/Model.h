#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <string>
#define safeRelease(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}

using namespace DirectX;
using namespace std;

class Model
{
public:
	string	ErrorMessage;
	Model();
	~Model();

	virtual void shutdown();

	XMFLOAT4X4*	WorldMatrix();
	ID3D11ShaderResourceView** Texture();
	ID3D11Buffer** VertexBuffer();
	ID3D11Buffer*	IndexBuffer();
	int	IndexCount();
protected:
	XMFLOAT4X4									_worldMatrix;
	ID3D11ShaderResourceView*		_texture;
	ID3D11Buffer*								_vertexBuffer;
	ID3D11Buffer*								_indexBuffer;
	int													_countIndexs;
};

class TextureModel : public Model
{
public:
	TextureModel() { ErrorMessage = "TextureModel"; }

	bool initialize();
	void shutdown();
};

