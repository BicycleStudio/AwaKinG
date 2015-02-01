#include "Engine.h"

Engine::Engine()
{
	_cameraMangerType = CMT_REDACTOR;
	ErrorMessage = "Engine";
	_active = true;
	_d3dRender = 0;
	_scene = 0;
	_camera = 0;
	_inputManager = 0;
}
void Engine::cameraManagerSwitch()
{
	switch(_cameraMangerType)
	{
	case CMT_REDACTOR:
		_cameraManager = _redactorCameraManager;
		break;
	case CMT_REDACTORFREE:
		_cameraManager = _redactorFreeCameraManager;
		break;
	}
}
bool Engine::initialize(HWND* hwnd, int sizeX, int sizeY)
{
	_d3dRender = &D3dRender::getInstance();
	_d3dRender->setInitialize(hwnd[0], sizeX, sizeY);
	safeInit(_d3dRender);
	_scene = &Scene::getInstance();
	safeInit(_scene);
	_parser = &Parser::getInstance();

	_inputManager = &InputManager::getInstance();
	_inputManager->setInitialize(hwnd[0]);
	safeInit(_inputManager);

	_camera = new Camera();

#pragma region Camera manager init
	//Create redactor now & use RedactorCameraManager;
	_redactorFreeCameraManager = new RedactorFreeCameraManager();
	_redactorFreeCameraManager->initialize(_camera);
	_redactorFreeCameraManager->setInputInterface(_inputManager);

	_redactorCameraManager = new RedactorCameraManager();
	_redactorCameraManager->initialize(_camera);
	_redactorCameraManager->setInputInterface(_inputManager);

	cameraManagerSwitch();
#pragma endregion

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
			// may be need to update direct input not every frame
			/*else if(msg_.message == WM_KEYDOWN)
			{
			}
			else if(msg_.message == WM_KEYUP)
			{
			}*/
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
				// need to think about this function!
				/*if(_keys[VK_ESCAPE])
				done_ = true;
				else*/
				{
					safeUpdate(_inputManager);
					//_scene->update();
					_cameraManager->update();
					//_camera->update();
					_d3dRender->render();
				}
			}
		}
	}
}
void Engine::setCameraManagerType(CameraManagerType cameraType)
{
	_cameraMangerType = cameraType;
	cameraManagerSwitch();
}
bool Engine::createMapFromFile(string fileName)
{
	if(!_parser->readFromFile(fileName)) 	{ ErrorMessage = "Create map error. Parser:\n" + _parser->ErrorMessage; return false; }

	return true;
}
