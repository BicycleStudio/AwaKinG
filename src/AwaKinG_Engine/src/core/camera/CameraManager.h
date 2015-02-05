#pragma once
#include "Camera.h"
#include "../input/InputManager.h"
#include <dinput.h>

class CameraManager
{
public:
	bool initialize(Camera *cam);
	CameraManager();
	~CameraManager();

	virtual void update();
protected:
	Camera*		_camera;
};

class RedactorCameraManager : public CameraManager
{
public:
	RedactorCameraManager()	{ _speed = 1.0f; }
	void setInputInterface();

	virtual void update();
	void setSpeed(float speed);
protected:
	IIMMouseKeyboard* _iInputManager;
	float							_speed;
};

class RedactorFreeCameraManager : public RedactorCameraManager
{
public:
	RedactorFreeCameraManager() {}

	virtual void update();
};