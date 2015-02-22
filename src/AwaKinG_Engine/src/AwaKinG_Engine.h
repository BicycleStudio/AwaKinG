#ifndef __AWAKING_ENGINE_H
#define __AWAKING_ENGINE_H

#ifdef AWAKINGDLL_EXPORTS
#define DLL_SPEC extern "C" __declspec(dllexport)

#else
#define DLL_SPEC extern "C" __declspec(dllimport)
#endif // AWAKINGDLL_EXPORTS

#include "core\Engine.h"

DLL_SPEC Engine* getEnginePointer();
/*
DLL_SPEC bool initialize(Engine* pointer, HWND mainHwnd, HWND hwnd, int sizeX, int sizeY);
DLL_SPEC void release(Engine* pointer);
DLL_SPEC bool update(Engine* pointer);
DLL_SPEC void setActive(Engine* pointer, bool value);
DLL_SPEC bool getActive(Engine* pointer);
DLL_SPEC bool resizeBuffer(Engine* pointer, int sizeX, int sizeY);
*/
#endif // __AWAKING_ENGINE_H 