#pragma once
#include "../render/D3dRender.h"
#include "InputManager.h"
#include "Scene.h"
#include "Camera.h"
#include <Windows.h>

#define safeInit(obj) if(!obj->initialize()) {MessageBox(NULL, obj->ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR); shutdown(); return false;}
#define safeUpdate(obj) if(!obj->update()) {MessageBox(NULL, obj->ErrorMessage.c_str(), "update error", MB_OK | MB_ICONERROR); done_; PostQuitMessage(0);shutdown();break; }
#define safeShutdown(obj) if(obj) {obj->shutdown(); obj = 0;}

class Engine
{
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

public:
	bool initialize(HWND* hwnd, int sizeX, int sizeY);
	void shutdown();
	void run();
	void setActive(bool value);
private:
	InputManager*		_inputManager;
	Camera*					_camera;
	D3dRender*			_d3dRender;
	Scene*					_scene;

	bool						_keys[256];
	bool						_active;
};

