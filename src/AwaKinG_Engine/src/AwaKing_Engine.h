#ifndef __AWAKING_ENGINE_H
#define __AWAKING_ENGINE_H

#ifdef AWAKINGDLL_EXPORTS
#define DLL_SPEC extern "C" __declspec(dllexport)

#else
#define DLL_SPEC extern "C" __declspec(dllimport)
#endif // AWAKINGDLL_EXPORTS

#include "core\Engine.h"

DLL_SPEC RedactorEngine* EngineGetPointer();
DLL_SPEC bool EngineInitialize(RedactorEngine* pointer, HWND mainHwnd, HWND hwnd, int sizeX, int sizeY);
DLL_SPEC void EngineRelease(RedactorEngine* pointer);
DLL_SPEC bool EngineUpdate(RedactorEngine* pointer);
DLL_SPEC void EngineCreateMapFromFile(RedactorEngine* pointer, const char* fileName, int len);
DLL_SPEC int EngineSetActive(RedactorEngine* pointer, int value);
DLL_SPEC bool EngineGetActive(RedactorEngine* pointer);
DLL_SPEC void EngineSetCameraManagerType(RedactorEngine* pointer, int type);
DLL_SPEC bool EngineRenderResizeBuffer(RedactorEngine* pointer, int sizeX, int sizeY);
DLL_SPEC bool EngineTerrainGenerate(RedactorEngine* pointer, int sizeX, int sizeY);
DLL_SPEC void EngineTerrainRandomize(RedactorEngine* pointer, int diapazon);
DLL_SPEC void EngineTerrainBlur(RedactorEngine* pointer, int value);
DLL_SPEC char* EngineTerrainSave(RedactorEngine* pointer, const char* fileName, int len);
DLL_SPEC void EngineTerrainLoad(RedactorEngine* pointer, const char* fileName, int len);

#endif // __AWAKING_ENGINE_H setCameraManagerType