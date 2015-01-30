#include "Engine.h"

Engine::Engine()
{
	_d3dRender = 0;
	_scene = 0;
	ErrorMessage = "Engine";
	_mayInitialized = false;
}
void Engine::setInitialize(HWND hwnd, int sizeX, int sizeY)
{
	_hwnd = hwnd;
	_sizeX = sizeX;
	_sizeY = sizeY;
	_mayInitialized = true;
}
bool Engine::initialize()
{
	if(!_mayInitialized) { ErrorMessage = "Set hwnd & size of render before initialize Engine"; return false; }
	_d3dRender = &D3dRender::getInstance();
	_d3dRender->setInitialize(_hwnd, _sizeX, _sizeY);
	safeInit(_d3dRender);
	_scene = &Scene::getInstance();
	safeInit(_scene);

	return true;
}
void Engine::shutdown()
{
	safeRelease(_d3dRender);
	safeRelease(_scene);
}
