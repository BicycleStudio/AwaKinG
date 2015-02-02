#pragma once
#include "../../../Include/dinput.h"		
//#include <dinput.h>
#include <vector>
#include "../../render/D3dRender.h"
#include "IInputManager.h"

#pragma comment(lib, "lib/x86/dinput8.lib")

class InputManager : public IInputManager
{
#pragma region Singleton
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
#pragma endregion

#pragma region Intarface methods
public:
	bool W();
	bool A();
	bool S();
	bool D();
	bool LShift();
	bool LControl();

	float MouseX();
	float MouseY();
	float MouseZ();
#pragma endregion

#pragma region Public methods
public:
	//Before initialize() call setInitialize(HWND hwnd)
	bool initialize();
	void setInitialize(HWND hwnd);

	bool update();
	bool acquire();

	void shutdown();

	DIMOUSESTATE* getMouseState();
	unsigned char** getKeyState();
#pragma endregion

#pragma region private vars
private:
	HWND										_hwnd;
	IDirectInput8*					_device;
	IDirectInputDevice8*		_mouse;
	IDirectInputDevice8*		_keyboard;
	bool										_mayInitialized;

	DIMOUSESTATE						_mouseState;
	bool						_keyState[256];
#pragma endregion
};

