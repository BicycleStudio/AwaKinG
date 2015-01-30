#pragma once
#include "../render/D3dRender.h"
#include "Scene.h"
#include <Windows.h>

#define safeInit(obj) if(!obj->initialize()) {MessageBox(NULL, obj->ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR); shutdown(); return false;}
#define safeRelease(obj) if(obj) {obj->shutdown(); obj = 0;}

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
	void setInitialize(HWND hwnd, int sizeX, int sizeY);
	bool initialize();
	void shutdown();
private:
	D3dRender*			_d3dRender;
	Scene*					_scene;
	bool						_mayInitialized;
	HWND						_hwnd;
	int							_sizeX;
	int							_sizeY;
};

