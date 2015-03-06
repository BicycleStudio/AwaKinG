#pragma once
#include"../../render/Additional.h"

class Entity {
public:
	Entity();
	~Entity();
	virtual void update();
  void updateTransform();
  void setPosition(XMFLOAT3& position);
  void setScaling(XMFLOAT3& scale);
  void setRotation(XMFLOAT3& rotation);
  XMFLOAT4X4* getWorldMatrix();

protected:
	XMFLOAT4X4*		_worldMatrix;
  XMFLOAT3      _position;
  XMFLOAT3      _scaling;
  XMFLOAT3      _rotation;
};

