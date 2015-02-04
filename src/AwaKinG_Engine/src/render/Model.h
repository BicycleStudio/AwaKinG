#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <string>
#define safeRelease(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}

using namespace DirectX;
using namespace std;

namespace Vertex 
{
	struct Simple
	{
		Simple() {}
		Simple(XMFLOAT3 pos, XMFLOAT2 tex) { position = pos; texCoord = tex; normal = XMFLOAT3(0.0f,1.0f,0.0f); }
		Simple(XMFLOAT3 pos, XMFLOAT2 tex, XMFLOAT3 nor) { position = pos; texCoord = tex; normal = nor; }

		XMFLOAT3	position;
		XMFLOAT2	texCoord;
		XMFLOAT3	normal;
	};
}
class Model
{
public:
	string	ErrorMessage;
	Model();
	~Model();

	virtual void shutdown();

	virtual void setBuffers(ID3D11Buffer* vbuf, ID3D11Buffer* ibuf, int indCount);
	void setTexture(ID3D11ShaderResourceView* texture);

	ID3D11ShaderResourceView** getTexture();
	ID3D11Buffer* getVertexBuffer();
	int	getIndexCount();


	ID3D11Buffer*								vertexBuffer;
protected:
	ID3D11ShaderResourceView*		_texture;
	int													_countIndexs;
};
class ModelEx : public Model
{
public:
	ModelEx() { _fileName = ""; _indexBuffer = 0; ErrorMessage = "ModelEx"; }
	virtual void setBuffers(ID3D11Buffer* vbuf, ID3D11Buffer* ibuf, int indCount);
	
	void shutdown();
	void setFileName(string fileName);
	const char*	getFileName();
	ID3D11Buffer*	getIndexBuffer();
protected:
	string											_fileName;
	ID3D11Buffer*								_indexBuffer;
};
class TextureModel : public ModelEx
{
public:
	TextureModel() { _fileName = ""; _indexBuffer = 0; ErrorMessage = "TextureModel"; }
protected:
};