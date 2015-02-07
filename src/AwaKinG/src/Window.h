#pragma once
#include <Windows.h>
#include <string>
class Window
{
public:
	std::string ErrorMessage;

	static Window& getInstance() 
	{
		static Window window;
		return window;
	};
	bool initialize(HWND* hwnd, int sizeX, int sizeY);
	void shutdown();
	int getWidth();
	int getHeight();
private:
	Window();
	Window(const Window&);
private:
	int					_width;
	int					_height;
	HWND		    _hWnd;
	bool        _fullscreen;
};
