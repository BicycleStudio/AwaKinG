#pragma once
#include "../render/D3dRender.h"
#include "input/InputManager.h"
#include "map/Scene.h"
#include "cammanager/Camera.h"
#include "cammanager/CameraManager.h"
#include "Parser.h"
#include <Windows.h>

#define safeInit(obj) if(!obj->initialize()) {MessageBox(NULL, obj->ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR); shutdown(); return false;}
#define safeUpdate(obj) if(!obj->update()) {MessageBox(NULL, obj->ErrorMessage.c_str(), "update error", MB_OK | MB_ICONERROR); done_; PostQuitMessage(0);shutdown();break; }
#define safeShutdown(obj) if(obj) {obj->shutdown(); obj = 0;}

class Engine
{
public:
	enum CameraManagerType { CMT_REDACTOR, CMT_REDACTORFREE };
#pragma region singleton
public:
	std::string ErrorMessage;
	static Engine& getInstance()
	{
		static Engine engine;
		return engine;
	};

private:
	Engine();
	Engine(const Engine&);
#pragma endregion

#pragma region public functions
public:
	void setCameraManagerType(CameraManagerType cameraType);
	bool initialize(HWND* hwnd, int sizeX, int sizeY);
	void shutdown();
	void run();
	void setActive(bool value);

	bool createMapFromFile(string fileName);
#pragma endregion

#pragma region private functions
private:
	void cameraManagerSwitch();
#pragma endregion

#pragma region private vars
private:
	InputManager*									_inputManager;
	CameraManagerType							_cameraMangerType;
	CameraManager*								_cameraManager;
	RedactorCameraManager*				_redactorCameraManager;
	RedactorFreeCameraManager*		_redactorFreeCameraManager;
	Camera*												_camera;
	D3dRender*										_d3dRender;
	Scene*												_scene;
	Parser*												_parser;

	bool													_active;
#pragma endregion
};

