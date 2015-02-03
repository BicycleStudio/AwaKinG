#pragma once
#include "Camera.h"
#include "../input/IInputManager.h"
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
	void setInputInterface(IInputManager* iinput);

	virtual void update();
protected:
	IInputManager* _iInputManager;
};

class RedactorFreeCameraManager : public RedactorCameraManager
{
public:
	RedactorFreeCameraManager() {}

	virtual void update();
};