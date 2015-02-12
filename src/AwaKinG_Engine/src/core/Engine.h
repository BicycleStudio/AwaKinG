#pragma once
#include "terrain/TerrainManager.h"
#include "input/InputManager.h"
#include "map/Scene.h"
#include "camera/CameraManager.h"
#include <Windows.h>

#pragma region Macros
#define safeSystemInit(obj) if(!obj.initialize()) {MessageBox(NULL, obj.ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR); shutdown(); return false;}
#define safeUpdate(obj) if(!obj.update()) {MessageBox(NULL, obj.ErrorMessage.c_str(), "update error", MB_OK | MB_ICONERROR); PostQuitMessage(0); shutdown(); return true; }
#define checkRenderResult(boolean) if(!boolean) {MessageBox(NULL, D3dRender::getInstance().ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR);  return false;}
#pragma endregion

class Engine
{  
public:
	enum CameraManagerType { CMT_REDACTOR, CMT_REDACTORFREE };
	std::string ErrorMessage;
#pragma region public functions
public:
	Engine();
	virtual bool initialize(HWND mainHwnd, HWND renderHwnd, int sizeX, int sizeY);
	virtual	void shutdown();
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
	bool													_systemInitialized;
	CameraManagerType							_cameraMangerType;
	CameraManager*								_cameraManager;
	RedactorCameraManager*				_redactorCameraManager;
	RedactorFreeCameraManager*		_redactorFreeCameraManager;
	bool													_active;
#pragma endregion
};

class RedactorEngine : public Engine
{
#pragma region public functions
public:
	RedactorEngine();

	// FOR C++ REDACTOR
	void setShortPaths();
	bool initialize(HWND mainHwnd, HWND renderHwnd, int sizeX, int sizeY);
	void shutdown();
#pragma endregion

#pragma region redactor functions
	void setCameraSpeed(float speed);

	void setTerrainPenVisible(bool set);
	void setTerrainQuadTreeVisible(bool set);
	void setTerrainWireframe(bool set);
	void saveTerrain(string fileName);
	void randomizeTerrain(int diapazon);
	void blurTerrain(int value);
	bool createTerrain(int gridX, int gridY);
	bool createMapFromFile(string fileName);
	void loadTerrain(string fileName);


	void terrainSetTerraPenSize(int in, int out);
	void terrainSetTerraPenHard(float hard);

	void terrainTerraformShow(int posX, int posY);
	void terrainTerraformApply(int posX, int posY);
//	void terrainTerraformApplyPosLock(int posX, int posY);
//	void terrainTerraformApplyShiftHeight(int posX, int posY);
//	void terrainTerraformApplyAltHard(int posX, int posY);
//	void terrainTerraformApplySmIn(int posX, int posY);
//	void terrainTerraformApplySmOut(int posX, int posY);
//	void terrainTerraformApplySmInOut(int posX, int posY);


	void textureWorkTerrain(int posX, int posY);
#pragma endregion

#pragma region private vars
private:
	RedactorTerrainManager*					_redactorTerrainManager;
#pragma endregion
};