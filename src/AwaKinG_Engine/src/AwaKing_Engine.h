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
DLL_SPEC void EngineSetActive(RedactorEngine* pointer, int value);
DLL_SPEC bool EngineGetActive(RedactorEngine* pointer);
DLL_SPEC void EngineCameraManagerSetType(RedactorEngine* pointer, int type);
DLL_SPEC bool EngineRenderResizeBuffer(RedactorEngine* pointer, int sizeX, int sizeY);
DLL_SPEC bool EngineTerrainGenerate(RedactorEngine* pointer, int sizeX, int sizeY);
DLL_SPEC void EngineTerrainRandomize(RedactorEngine* pointer, int diapazon);
DLL_SPEC void EngineTerrainBlur(RedactorEngine* pointer, int value);
DLL_SPEC void EngineTerrainSave(RedactorEngine* pointer, const char* fileName, int len);
DLL_SPEC void EngineTerrainLoad(RedactorEngine* pointer, const char* fileName, int len);
DLL_SPEC void EngineCameraManagerSetSpeed(RedactorEngine* pointer, float speed);
DLL_SPEC void EngineTerrainQuadTreeSetVisible(RedactorEngine* pointer, bool set);
DLL_SPEC void EngineTerrainSetWireframe(RedactorEngine* pointer, bool set);
DLL_SPEC void EngineTerrainTerraformingShow(RedactorEngine* pointer, int posX, int posY);
DLL_SPEC void EngineTerrainTerraformingApply(RedactorEngine* pointer, int posX, int posY);

DLL_SPEC void EngineTerrainSetTerraPenSize(RedactorEngine* pointer, int in, int out);
DLL_SPEC void EngineTerrainSetTerraPenHard(RedactorEngine* pointer, float hard);
#endif // __AWAKING_ENGINE_H setCameraManagerType