#ifndef __ENTITY_H
#define __ENTITY_H
#include"../../render/Additional.h"
#include"../../render/Camera.h"
#include"../../core/Input.h"

class Entity {
public:
	Entity();
	~Entity();
	virtual void update();
  void updateTransform();
  void updateTranslation();
  void setPosition(XMFLOAT3& position);
  void setScaling(XMFLOAT3& scale);
  void setRotation(XMFLOAT3& rotation);
  void setModelName(string name);
  string& getModelName();
  XMFLOAT4X4*    getWorldMatrix();
  XMFLOAT3*      getPosition();
  XMFLOAT3*      getScale();
  XMFLOAT3*      getRotation();
protected:
	XMFLOAT4X4*		_worldMatrix;
  XMFLOAT3      _position;
  XMFLOAT3      _scaling;
  XMFLOAT3      _rotation;
  string        _modelName;
  float				  _speed;
};
class Player : public Entity {
public:
  Player();
  ~Player();
  virtual void update();

public:
  void setTarger(Entity* entity);
  void walk(XMFLOAT3* pos, float units);
  void strafe(float units);

private:
  Entity*     _target;
  XMFLOAT3    _look;
  XMFLOAT3    _up;
  XMFLOAT3    _right;
  float       _distanceToCamera;
};
class FirstPersonPlayer : public Entity {
public:
  FirstPersonPlayer();
  ~FirstPersonPlayer();
  void update();
};
class FirstPersonFreePlayer : public Entity {
public:
  FirstPersonFreePlayer();
  ~FirstPersonFreePlayer();
  void update();
};
class RedactorPlayer : public Entity {
public:
  RedactorPlayer();
  ~RedactorPlayer();
  void update();
};
#endif