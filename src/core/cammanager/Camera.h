#pragma once
#include "../../render/D3dRender.h"
class Camera
{
public:
	Camera();
	~Camera();
	void shutdown();
	void update();
	XMFLOAT4X4* getViewMatrixPointer();

	void pitch(float angle);
	void yaw(float angle);
	void walk(float units);
	void strafe(float units);
private:
	XMFLOAT4X4 _viewMatrixRender;
	XMFLOAT3 _position;
	XMFLOAT3 _look;
	XMFLOAT3 _up;
	XMFLOAT3 _right;
};
