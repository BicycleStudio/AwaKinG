#include "Model.h"

#pragma region Model
Model::Model() {
	_vertexBuffer = 0;
	_indexBuffer = 0;
}
Model::~Model() {
	SAFE_RELEASE(_vertexBuffer);
	SAFE_RELEASE(_indexBuffer);
}
ID3D11Buffer** Model::getVertexBuffer() {
	return &_vertexBuffer;
}
ID3D11Buffer* Model::getIndexBuffer() {
	return _indexBuffer;
}
int	Model::getIndexCount() {
	return _indexCount;
}
ID3D11ShaderResourceView** Model::getDiffuseMap() {
	return 0;
}
#pragma endregion

#pragma region TextureModel
TextureModel::TextureModel() {
	_vertexBuffer = 0;
	_indexBuffer = 0;
	_diffuseMap = 0;
}
TextureModel::~TextureModel() {
	SAFE_RELEASE(_vertexBuffer);
	SAFE_RELEASE(_indexBuffer);
	SAFE_RELEASE(_diffuseMap);
}
ID3D11ShaderResourceView** TextureModel::getDiffuseMap() {
	return &_diffuseMap;
}
#pragma endregion
