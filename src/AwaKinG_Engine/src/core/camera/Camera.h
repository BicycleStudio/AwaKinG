#pragma once
#include "../../render/D3dRender.h"
class Camera
{
public:
	static Camera& getInstance()
	{
		static Camera cam;
		return cam;
	}
private:
	Camera();
	Camera(const Camera&);

public:
	void shutdown();
	void update();
	XMFLOAT4X4* getViewMatrixPointer();
	XMFLOAT3* getPositionPointer();
	XMFLOAT3* getLookPointer();

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
