#include "Model.h"

Model::Model()
{
	ErrorMessage = "Model";
	_countIndexs = 0;
	_vertexBuffer = 0;
	_texture = 0;
}
Object::Object()
{
	ErrorMessage = "ColorObject";
	_countIndexs = 0;
	_vertexBuffer = 0;
}
void Object::shutdown()
{
	safeRelease(_vertexBuffer);
}
void Object::setBuffers(ID3D11Buffer* vbuf, ID3D11Buffer* ibuf, int indCount)
{
	_vertexBuffer = vbuf;
	_countIndexs = indCount;
}
float4* SystemModel::getColor()
{
	return &_color;
}
Model::~Model()
{
}
ID3D11ShaderResourceView** Model::getTexture()
{
	return &_texture;
}
ID3D11Buffer** Object::getVertexBuffer()
{
	return &_vertexBuffer;
}
int Object::getIndexCount()
{
	return _countIndexs;
}
void Model::shutdown()
{
	safeRelease(_vertexBuffer);
	safeRelease(_texture);
}
void Model::setTexture(ID3D11ShaderResourceView* texture)
{
	_texture = texture;
}
void ModelEx::shutdown()
{
	safeRelease(_indexBuffer);
	safeRelease(_vertexBuffer);
	safeRelease(_texture);
}
const char*	ModelEx::getFileName()
{
	return _fileName.c_str();
}
void ModelEx::setFileName(string fileName)
{
	_fileName = fileName;
}
ID3D11Buffer*	ModelEx::getIndexBuffer()
{
	return _indexBuffer;
}
void ModelEx::setBuffers(ID3D11Buffer* vbuf, ID3D11Buffer* ibuf, int indCount)
{
	_vertexBuffer = vbuf;
	_indexBuffer = ibuf;
	_countIndexs = indCount;
}
