#pragma once
#include"../../render/Additional.h"

class Entity {
public:
	Entity();
	~Entity();
	void update();

private:
	XMFLOAT4X4*		_worldMatrix;
};

