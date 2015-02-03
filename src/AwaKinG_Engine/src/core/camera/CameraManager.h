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
	RedactorCameraManager(){}
	void setInputInterface();

	virtual void update();
protected:
	IIMMouseKeyboard* _iInputManager;
};

class RedactorFreeCameraManager : public RedactorCameraManager
{
public:
	RedactorFreeCameraManager() {}

	virtual void update();
};