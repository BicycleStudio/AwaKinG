#include "Model.h"

Model::Model()
{
	ErrorMessage = "Model";
	_countIndexs = 0;
	vertexBuffer = 0;
	_texture = 0;
}
Model::~Model()
{
}
ID3D11ShaderResourceView** Model::getTexture()
{
	return &_texture;
}
ID3D11Buffer* Model::getVertexBuffer()
{
	return vertexBuffer;
}

int Model::getIndexCount()
{
	return _countIndexs;
}
void Model::shutdown()
{
	safeRelease(vertexBuffer);
	safeRelease(_texture);
}
void Model::setBuffers(ID3D11Buffer* vbuf, ID3D11Buffer* ibuf, int indCount)
{
	vertexBuffer = vbuf;
	_countIndexs = indCount;
}
void Model::setTexture(ID3D11ShaderResourceView* texture)
{
	_texture = texture;
}
void ModelEx::shutdown()
{
	safeRelease(_indexBuffer);
	safeRelease(vertexBuffer);
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
	vertexBuffer = vbuf;
	_indexBuffer = ibuf;
	_countIndexs = indCount;
}