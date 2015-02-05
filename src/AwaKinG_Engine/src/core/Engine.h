#pragma once
#include "terrain/TerrainManager.h"
#include "input/InputManager.h"
#include "map/Scene.h"
#include "camera/Camera.h"
#include "camera/CameraManager.h"
#include <Windows.h>

#define safeSystemInit(obj) if(!obj->initialize()) {MessageBox(NULL, obj->ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR); shutdown(); return false;}
#define safeUpdate(obj) if(!obj->update()) {MessageBox(NULL, obj->ErrorMessage.c_str(), "update error", MB_OK | MB_ICONERROR); PostQuitMessage(0); shutdown(); return true; }
#define safeShutdown(obj) if(obj) {obj->shutdown(); obj = 0;}
#define checkRenderResult(boolean) if(!boolean) {MessageBox(NULL, _d3dRender->ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR);  return false;}

class Engine
{  
public:
	enum CameraManagerType { CMT_REDACTOR, CMT_REDACTORFREE };
	std::string ErrorMessage;
	Engine();

#pragma region public functions
public:
	bool initialize(HWND mainHwnd, HWND renderHwnd, int sizeX, int sizeY);
	void shutdown();
	bool active();
	bool update();
	void setActive(bool value);
	bool resizeRenderBuffer(int sizeX, int sizeY);

	void setCameraManagerType(CameraManagerType cameraType);
	virtual void loadTerrain(string fileName);
#pragma endregion

#pragma region private functions
protected:
	void _cameraManagerSwitch();
	bool _createEntity(Entity** entity, string fileName);
#pragma endregion

#pragma region private vars
private:
	TerrainManager*								_terrainManager;
protected:
	bool													_shortPaths;
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

class RedactorEngine : public Engine
{
public:
	RedactorEngine();

	// FOR C++ REDACTOR
	void setShortPaths();

#pragma region redactor functions
	void saveTerrain(string fileName);
	void randomizeTerrain(int diapazon);
	void blurTerrain(int value);
	bool createTerrain(int gridX, int gridY);
	bool createMapFromFile(string fileName);
	void loadTerrain(string fileName);

	void setTerrainWorkType(int type);
	int pickTerrain(int posX, int posY);
#pragma endregion
private: 
	RedactorTerrainManager*								_redactorTerrainManager;
};