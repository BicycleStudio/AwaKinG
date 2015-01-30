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
	bool initialize();
	void shutdown();
	HWND getWindow(int* sizeX, int* sizeY);
private:
	Window();
	Window(const Window&);
private:
	int					_width;
	int					_height;
	HWND		    _hWnd;
	bool        _fullscreen;
};
