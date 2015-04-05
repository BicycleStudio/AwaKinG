#ifndef __INPUT_H
#define __INPUT_H
#define DIRECTINPUT_VERSION 0x0800
#include <Windows.h>
#include <vector>
#include "../ErrorDefines.h"
#include "../render/Additional.h"
#include "../../../../include/dinput.h"		

#ifdef __x86
#pragma comment(lib, "../../lib/x86/dinput8.lib")
#pragma comment(lib, "../../lib/x86/dxguid.lib")
#endif
#ifdef __x64
#pragma comment(lib, "../../lib/x64/dinput8.lib")
#pragma comment(lib, "../../lib/x64/dxguid.lib")
#endif

using namespace std;

class Input
{
public:
  string errorMessage;
  bool update();
  void shutdown();
  bool initialize(HWND hwnd);
  bool acquire();

  bool W();
  bool A();
  bool S();
  bool D();
  bool LShift();
  bool LControl();

  float MouseX();
  float MouseY();
  float MouseZ();

	static Input& getInstance()  {
		static Input input_;
		return input_;
	}
private:
	Input();
	Input(const Input&);

  HWND										_hwnd;
  IDirectInput8*					_device;
  IDirectInputDevice8*		_mouse;
  IDirectInputDevice8*		_keyboard;

  DIMOUSESTATE						_mouseState;
  bool						        _keyState[256];
};
#endif // __INPUT_H 