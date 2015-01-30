#pragma once
#include "../render/D3dRender.h"
class Camera
{
public:
	bool** Keys;

	Camera();
	~Camera();
	void shutdown();
	void update();
	XMFLOAT4X4* getViewMatrixPointer();

protected:
	void calculateViewMatrix();
	virtual void Pitch(float angle);
	virtual void Yaw(float angle);
	virtual void Walk(float units);
	virtual void Strafe(float units);
protected:
	XMFLOAT4X4 _viewMatrixRender;
	XMFLOAT3 _position;
	XMFLOAT3 _look;
	XMFLOAT3 _up;
	XMFLOAT3 _right;
};
class RedactorCam : public Camera
{

};

