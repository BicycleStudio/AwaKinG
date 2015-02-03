#pragma once
class IInputManager
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

