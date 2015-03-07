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
void Model::setVertexBuffer(ID3D11Buffer* buffer) {
  _vertexBuffer = buffer;
}
void Model::setIndexBuffer(ID3D11Buffer* buffer, int countIndexs) {
  _indexBuffer = buffer;
  _indexCount = countIndexs;
}
void Model::setName(string name) {
  _name = name;
}
string Model::getName() {
  return _name;
}
#pragma endregion

#pragma region TextureModel
TextureModel::TextureModel(string name) {
	_diffuseMap = 0;
  _name = name;
}
TextureModel::~TextureModel() {
	SAFE_RELEASE(_diffuseMap);
}
ID3D11ShaderResourceView** TextureModel::getDiffuseMap() {
	return &_diffuseMap;
}
#pragma endregion
