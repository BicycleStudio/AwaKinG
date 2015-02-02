#include "Model.h"

Model::Model()
{
	_fileName = "";
	ErrorMessage = "Model";
	_countIndexs = 0;
	_indexBuffer = 0;
	_vertexBuffer = 0;
	_texture = 0;
}
Model::~Model()
{
}
ID3D11ShaderResourceView** Model::getTexture()
{
	return &_texture;
}
ID3D11Buffer** Model::getVertexBuffer()
{
	return &_vertexBuffer;
}
ID3D11Buffer*	Model::getIndexBuffer()
{
	return _indexBuffer;
}
int Model::getIndexCount()
{
	return _countIndexs;
}
void Model::shutdown()
{
	safeRelease(_indexBuffer);
	safeRelease(_vertexBuffer);
	safeRelease(_texture);
}
void Model::setBuffers(ID3D11Buffer* vbuf, ID3D11Buffer* ibuf, int indCount)
{
	_vertexBuffer = vbuf;
	_indexBuffer = ibuf;
	_countIndexs = indCount;
}
void Model::setTexture(ID3D11ShaderResourceView* texture)
{
	_texture = texture;
}
void TextureModel::shutdown()
{
	safeRelease(_indexBuffer);
	safeRelease(_vertexBuffer);
	safeRelease(_texture);
}
const char*	Model::getFileName()
{
	return _fileName.c_str();
}
void Model::setFileName(string fileName)
{
	_fileName = fileName;
}
