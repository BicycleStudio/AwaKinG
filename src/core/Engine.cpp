#include "Engine.h"

Engine::Engine()
{
	ErrorMessage = "Engine";
	_active = true;
	_d3dRender = 0;
	_scene = 0;
	_camera = 0;
	_inputManager = 0;
}
bool Engine::initialize(HWND* hwnd, int sizeX, int sizeY)
{
	_d3dRender = &D3dRender::getInstance();
	_d3dRender->setInitialize(hwnd[0], sizeX, sizeY);
	safeInit(_d3dRender);
	_scene = &Scene::getInstance();
	safeInit(_scene);

	_inputManager = &InputManager::getInstance();
	_inputManager->setInitialize(hwnd[0]);
	safeInit(_inputManager);

	_camera = new Camera();
	_camera->Keys[0] = _keys;
	_d3dRender->ViewMatrix = _camera->getViewMatrixPointer();

	return true;
}
void Engine::shutdown()
{
	safeShutdown(_d3dRender);
	safeShutdown(_scene);
	safeShutdown(_camera);
}
void Engine::setActive(bool value)
{
	_active = value;
	if(_active && _inputManager) _inputManager->acquire();
}
void Engine::run()
{
	MSG msg_;
	bool done_ = false;
	while(!done_)
	{
		if(PeekMessage(&msg_, NULL, 0, 0, PM_REMOVE))
		{

			if(msg_.message == WM_QUIT)
			{
				done_ = true;
			}
			else if(msg_.message == WM_KEYDOWN)
			{
				_keys[msg_.wParam] = true;
			}
			else if(msg_.message == WM_KEYUP)
			{
				_keys[msg_.wParam] = false;
			}
			else
			{
				TranslateMessage(&msg_);
				DispatchMessage(&msg_);
			}
		}
		else 
		{
			if(_active)
			{
				if(_keys[VK_ESCAPE])
					done_ = true;
				else
				{
					safeUpdate(_inputManager);
					//_scene->update();
					_camera->update();
					_d3dRender->render();
				}
			}
		}
	}
}