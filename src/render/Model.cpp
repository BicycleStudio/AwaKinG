#include "Model.h"

Model::Model()
{
	ErrorMessage = "Model";
	_countIndexs = 0;
	_indexBuffer = 0;
	_vertexBuffer = 0;
	_texture = 0;
	XMStoreFloat4x4(&_worldMatrix, XMMatrixIdentity());
}
Model::~Model()
{
}
XMFLOAT4X4* Model::WorldMatrix()
{
	return &_worldMatrix;
}
ID3D11ShaderResourceView** Model::Texture()
{
	return &_texture;
}
ID3D11Buffer** Model::VertexBuffer()
{
	return &_vertexBuffer;
}
ID3D11Buffer*	Model::IndexBuffer()
{
	return _indexBuffer;
}
int Model::IndexCount()
{
	return _countIndexs;
}
void Model::shutdown()
{
	safeRelease(_indexBuffer);
	safeRelease(_vertexBuffer);
	safeRelease(_texture);
}
void TextureModel::shutdown()
{
	safeRelease(_indexBuffer);
	safeRelease(_vertexBuffer);
	safeRelease(_texture);
}
bool TextureModel::initialize()
{

	return true;
}

