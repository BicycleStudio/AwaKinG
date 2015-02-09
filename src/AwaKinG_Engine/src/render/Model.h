#pragma once

#include "../../../../include/d3d11.h"
#include "../../../../include/xnamath.h"

#include <string>
#define safeRelease(d3dpointer) if(d3dpointer){d3dpointer->Release(); d3dpointer = 0;}

using namespace std;

typedef XMFLOAT4 float4;
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
	struct System
	{
		System() {}
		System(float3 pos) { position = pos; }

		float3	position;
	};
}
class Object
{
public:
	Object();

	string	ErrorMessage;
	virtual void shutdown();
	virtual void setBuffers(ID3D11Buffer* vbuf, ID3D11Buffer* ibuf, int indCount);
	
	ID3D11Buffer** getVertexBuffer();
	int	getIndexCount();
protected:
	ID3D11Buffer*								_vertexBuffer;
	int													_countIndexs;
};
class Model : public Object
{
public:
	Model();
	~Model();
	virtual void shutdown();
	void setTexture(ID3D11ShaderResourceView* texture);

	ID3D11ShaderResourceView** getTexture();
protected:
	ID3D11ShaderResourceView*		_texture;
};
class ModelEx : public Model
{
public:
	ModelEx() { _fileName = ""; _vertexBuffer = 0; _indexBuffer = 0; ErrorMessage = "ModelEx"; }
	virtual void setBuffers(ID3D11Buffer* vbuf, ID3D11Buffer* ibuf, int indCount);
	
	void shutdown();
	void setFileName(string fileName);
	const char*	getFileName();
	ID3D11Buffer*	getIndexBuffer();
	virtual float4* getColor(){ return NULL; }
protected:
	string											_fileName;
	ID3D11Buffer*								_indexBuffer;
};
class SystemModel : public ModelEx
{
public:
	SystemModel(){ _color = float4(0.0f, 1.0f, 0.0f, 1.0f); _fileName = ""; _vertexBuffer = 0; _indexBuffer = 0; ErrorMessage = "SystemModel"; }

	float4* getColor();
protected:
	float4			_color;
};
class TextureModel : public ModelEx
{
public:
	TextureModel() { _fileName = ""; _vertexBuffer = 0; _indexBuffer = 0; ErrorMessage = "TextureModel"; }
protected:
};