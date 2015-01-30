#pragma once
#include <dinput.h>
#include <vector>
#include "../render/D3dRender.h"

class InputManager
{
public:
	std::string ErrorMessage;
	static InputManager& getInstance()
	{
		static InputManager imanager;
		return imanager;
	};

private:
	InputManager();
	InputManager(const InputManager&);

public:
	//Before initialize() call setInitialize(HWND hwnd)
	bool initialize();
	void setInitialize(HWND hwnd);

	bool update();
	bool acquire();

	void shutdown();
private:
	HWND										_hwnd;
	IDirectInput8*					_device;
	IDirectInputDevice8*		_mouse;
	IDirectInputDevice8*		_keyboard;
	bool										_mayInitialized;

	DIMOUSESTATE						_mouseState;
	unsigned char						_keyState[256];
};

