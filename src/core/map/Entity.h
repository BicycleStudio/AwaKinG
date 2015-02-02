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
	void setTransformation(XMFLOAT3 pos, XMFLOAT3 scl, XMFLOAT3 rot);

protected:
	XMFLOAT4X4*	_worldMatrix;
};

