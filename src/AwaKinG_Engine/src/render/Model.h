#pragma once

#include "../../../../include/d3d11.h"
#include "../../../../include/xnamath.h"

//#include <DirectXMath.h>
//#include <d3d11.h>
#include <string>
#define safeRelease(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}

using namespace std;

typedef XMFLOAT3 float3;
typedef XMFLOAT2 float2;
typedef XMFLOAT4X4 float4x4;

namespace Vertex 
{
	struct Simple
	{
		Simple() {}
		Simple(float3 pos, float2 tex) { position = pos; texCoord = tex; normal = float3(0.0f, 1.0f, 0.0f); }
		Simple(float3 pos, float2 tex, float3 nor) { position = pos; texCoord = tex; normal = nor; }

		float3	position;
		float2	texCoord;
		float3	normal;
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