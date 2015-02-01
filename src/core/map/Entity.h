#pragma once
#include "../../render/D3dRender.h"
class Entity
{
public:
	Entity();
	~Entity();

	bool initialize(XMFLOAT4X4* worldMatrix);
	void update();
	void shutdown();

protected:
	XMFLOAT4X4*	_worldMatrix;
};

