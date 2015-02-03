#ifndef __AWAKING_ENGINE_H
#define __AWAKING_ENGINE_H

#ifdef AWAKINGDLL_EXPORTS
#define DLL_SPEC extern "C" __declspec(dllexport)

#else
#define DLL_SPEC extern "C" __declspec(dllimport)
#endif // AWAKINGDLL_EXPORTS

#include "core\Engine.h"

DLL_SPEC Engine* EngineGetPointer();
DLL_SPEC bool EngineInitialize(Engine* pointer, HWND mainHwnd, HWND hwnd, int sizeX, int sizeY);
DLL_SPEC void EngineRelease(Engine* pointer);
DLL_SPEC bool EngineUpdate(Engine* pointer);
DLL_SPEC void EngineCreateMapFromFile(Engine* pointer, const char* fileName, int len);
DLL_SPEC int EngineSetActive(Engine* pointer, int value);
DLL_SPEC bool EngineGetActive(Engine* pointer);
DLL_SPEC void EngineSetCameraManagerType(Engine* pointer, int type);
DLL_SPEC bool EngineRenderResizeBuffer(Engine* pointer, int sizeX, int sizeY);

#endif // __AWAKING_ENGINE_H setCameraManagerType