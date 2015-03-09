#ifndef __MODEL_H
#define __MODEL_H

#include "Additional.h"

class Model {
public:
  Model();
	~Model();

  void setVertexBuffer(ID3D11Buffer* buffer);
  void setIndexBuffer(ID3D11Buffer* buffer, int countIndexs);
	ID3D11Buffer** getVertexBuffer();
	ID3D11Buffer* getIndexBuffer();
  virtual ID3D11ShaderResourceView** getDiffuseMap();
  virtual void setDiffuseMap(ID3D11ShaderResourceView* srv);
	int	getIndexCount();
  void setName(string name);
  string getName();
protected:
	ID3D11Buffer* _vertexBuffer;
	ID3D11Buffer* _indexBuffer;
	int						_indexCount;
  string        _name;
};

class TextureModel : public Model {
public:
  TextureModel(string name);
  ~TextureModel();

	ID3D11ShaderResourceView** getDiffuseMap();
  void setDiffuseMap(ID3D11ShaderResourceView* srv);
protected:
	ID3D11ShaderResourceView* _diffuseMap;
};
#endif // __MODEL_H 