#ifndef __AWAKING_ENGINE_H
#define __AWAKING_ENGINE_H

#ifdef AWAKINGDLL_EXPORTS
#define DLL_SPEC extern "C" __declspec(dllexport)

#else
#define DLL_SPEC extern "C" __declspec(dllimport)
#endif // AWAKINGDLL_EXPORTS

#include "core/map/Map.h"
#include "core/map/Terrain.h"
#include "core/Engine.h"
#include "render/Render.h"
#include "core/Input.h"

DLL_SPEC bool initialize(HWND mainHwnd, HWND hwnd);
DLL_SPEC void release();
DLL_SPEC void update();
DLL_SPEC void setActive(bool value);
DLL_SPEC void resizeBuffer(int sizeX, int sizeY);
//  type { 0 = Player, 1 = FirstPerson, 2 = Redactor }
DLL_SPEC void setCameraType(int type);  
DLL_SPEC bool openMap(const char* fileName, int lenght);
DLL_SPEC bool saveMap(const char* fileName, int lenght);
DLL_SPEC void newMap();
DLL_SPEC int createTerrain(int sizeX, int sizeY);

#endif // __AWAKING_ENGINE_H 