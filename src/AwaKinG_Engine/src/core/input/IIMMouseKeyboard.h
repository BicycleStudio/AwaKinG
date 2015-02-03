#pragma once
#include "../../../../../Include/dinput.h"		
#include "../../render/D3dRender.h"
#pragma comment(lib, "../../lib/x86/dinput8.lib")

class IIMMouseKeyboard
{
public:
	virtual bool W() { return false; };
	virtual bool A() { return false; };
	virtual bool S() { return false; };
	virtual bool D() { return false; };

	virtual	bool LShift() { return false; };
	virtual	bool LControl() { return false; };

	virtual float MouseX() { return 0.0f; }
	virtual float MouseY() { return 0.0f; }
	virtual float MouseZ() { return 0.0f; }

	virtual bool MouseLeftButton() { return false; }
	virtual bool MouseRightButton() { return false; }
	virtual bool MouseCenterButton() { return false; }
};

