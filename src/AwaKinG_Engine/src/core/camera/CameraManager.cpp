#include "CameraManager.h"

CameraManager::CameraManager()
{
}
CameraManager::~CameraManager()
{
}
bool CameraManager::initialize(Camera *cam)
{
	_camera = cam;
	return true;
}
void CameraManager::update()
{

}
void RedactorCameraManager::setInputInterface()
{
	_iInputManager = &InputManager::getInstance();
}
void RedactorCameraManager::update()
{
	float delta = 1.0f;
	if(_iInputManager->LShift())
		delta = 8.0f;

	if(_iInputManager->LControl())
	{
		_camera->yaw(_iInputManager->MouseX());
		_camera->pitch(_iInputManager->MouseY());
	}
	_camera->walk(_iInputManager->MouseZ() * delta);

	_camera->update();
}
void RedactorFreeCameraManager::update()
{
	float delta = 0.1f;
	if(_iInputManager->LShift())
		delta = 4.0f;

	_camera->yaw(_iInputManager->MouseX());
	_camera->pitch(_iInputManager->MouseY());

	if(_iInputManager->W())
		_camera->walk(1.1f * delta);
	if(_iInputManager->A())
		_camera->strafe(-1.1f * delta);
	if(_iInputManager->S())
		_camera->walk(-1.1f * delta);
	if(_iInputManager->D())
		_camera->strafe(1.1f * delta);

	_camera->update();
}