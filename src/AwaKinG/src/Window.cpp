#include "Window.h"

#define BITZ 32

LRESULT CALLBACK WndProc(HWND	hWnd, UINT	uMsg, WPARAM	wParam, LPARAM	lParam);

Window::Window()
{
	ErrorMessage = "Window";
	_fullscreen = false;
	_hWnd = NULL;
}
bool Window::initialize(HWND* hwnd, int sizeX, int sizeY)
{
	HINSTANCE hInstance_ = GetModuleHandle(NULL);
	_width = sizeX;
	_height = sizeY;

	DWORD		dwExStyle_;
	DWORD		dwStyle_;
	RECT		windowRect_;

	if(MessageBox(NULL, "Would You Like To Run In Fullscreen Mode?", "Start FullScreen?", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		_fullscreen = true;
		HDC hDC_ = GetDC(NULL);
		_width = GetDeviceCaps(hDC_, HORZRES);
		_height = GetDeviceCaps(hDC_, VERTRES);
		ReleaseDC(NULL, hDC_);
	}

	windowRect_.left = (long)0;
	windowRect_.right = (long)_width;
	windowRect_.top = (long)0;
	windowRect_.bottom = (long)_height;

	WNDCLASS	wc_;
	wc_.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc_.lpfnWndProc = (WNDPROC)WndProc;
	wc_.cbClsExtra = 0;
	wc_.cbWndExtra = 0;
	wc_.hInstance = hInstance_;
	wc_.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc_.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc_.hbrBackground = NULL;
	wc_.lpszMenuName = NULL;
	wc_.lpszClassName = "AwaKinG";

	if(!RegisterClass(&wc_))	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	if(_fullscreen) 
	{
		DEVMODE dmScreenSettings_;
		memset(&dmScreenSettings_, 0, sizeof(dmScreenSettings_));
		dmScreenSettings_.dmSize = sizeof(dmScreenSettings_);
		dmScreenSettings_.dmPelsWidth = _width;
		dmScreenSettings_.dmPelsHeight = _height;
		dmScreenSettings_.dmBitsPerPel = BITZ;
		dmScreenSettings_.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if(ChangeDisplaySettings(&dmScreenSettings_, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if(MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "AwaKinG", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				_fullscreen = false;
				_width = sizeX;
				_height = sizeY;
				windowRect_.right = (long)_width;
				windowRect_.bottom = (long)_height;
			}
			else
			{
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return false;
			}
		}
	}
	if(_fullscreen) 
	{
		dwExStyle_ = WS_EX_APPWINDOW;
		dwStyle_ = WS_POPUP;
		ShowCursor(FALSE);
	}
	else 
	{
		dwExStyle_ = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle_ = WS_OVERLAPPEDWINDOW;
	}
	AdjustWindowRectEx(&windowRect_, dwStyle_, FALSE, dwExStyle_);
	if(!(_hWnd = CreateWindowEx(dwExStyle_,
		"AwaKinG",
		"AwaKinG v0.0",
		dwStyle_ |
		WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN,
		0, 0,
		windowRect_.right - windowRect_.left,
		windowRect_.bottom - windowRect_.top,
		NULL,
		NULL,
		hInstance_,
		NULL))) {
		shutdown();
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	ShowWindow(_hWnd, SW_SHOW);
	SetForegroundWindow(_hWnd);
	SetFocus(_hWnd);

	hwnd[0] = _hWnd;

	return true;
}
void Window::shutdown() 
{
	if(_fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);			
		ShowCursor(false);									
	}
	if(_hWnd && !DestroyWindow(_hWnd)) 
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		_hWnd = NULL;
	}
	if(!UnregisterClass("AwaKinG", GetModuleHandle(NULL)))
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
	}
}
int Window::getWidth()
{
	return _width;
}
int Window::getHeight()
{
	return _height;
}