#include "InputManager.h"

InputManager::InputManager()
{
	_device = 0;
	_keyboard = 0;
	_mouse = 0;
	_mayInitialized = false;
}

bool InputManager::initialize()
{
	if(!_mayInitialized){ ErrorMessage = "hwnd not found. InputManager"; return false; }
	checkResult(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&_device, NULL),
		"Creation of direct input device failed");

	checkResult(_device->CreateDevice(GUID_SysMouse, &_mouse, NULL),
		"Creation of direct input mouse failed");
	checkResult(_mouse->SetDataFormat(&c_dfDIMouse),
		"Setting data format direct input mouse failed");
	checkResult(_mouse->SetCooperativeLevel(_hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND),
		"Setting cooperaive level of mouse failed");

	checkResult(_device->CreateDevice(GUID_SysKeyboard, &_keyboard, NULL),
		"Creation of direct input keyboard failed");
	checkResult(_keyboard->SetDataFormat(&c_dfDIKeyboard),
		"Setting data format direct input mouse keyboard");
	checkResult(_keyboard->SetCooperativeLevel(_hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND),
		"Setting cooperaive level of keyboard failed");

	return acquire();
}
bool InputManager::acquire()
{
	checkResult(_mouse->Acquire(), "mouse acquire");
	checkResult(_keyboard->Acquire(), "keyboard acquire");
	return true;
}

void InputManager::shutdown()
{
	safeRelease(_mouse);
	safeRelease(_keyboard);
	safeRelease(_device);
}

void InputManager::setInitialize(HWND hwnd)
{
	_mayInitialized = true;
	_hwnd = hwnd;
}

bool InputManager::update()
{
	checkResult(_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&_mouseState),
		"GetDeviceState for mouse");
	checkResult(_keyboard->GetDeviceState(sizeof(_keyState), (LPVOID)&_keyState),
		"GetDeviceState for keyboard");
	
	return true;
}
