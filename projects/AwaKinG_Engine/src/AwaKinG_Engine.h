#ifndef __AWAKING_ENGINE_H
#define __AWAKING_ENGINE_H

#ifdef AWAKINGDLL_EXPORTS
#define DLL_SPEC extern "C" __declspec(dllexport)

#else
#define DLL_SPEC extern "C" __declspec(dllimport)
#endif // AWAKINGDLL_EXPORTS

#include "core/map/Map.h"
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

#endif // __AWAKING_ENGINE_H 