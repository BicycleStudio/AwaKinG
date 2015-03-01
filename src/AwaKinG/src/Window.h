#pragma once
#include <Windows.h>
#include <string>

class Window;

class DestroyerWindow
{
public:
  ~DestroyerWindow();
  void initialize(Window *p_window);
private:
  Window *_window;
};

class Window
{
public:
	std::string ErrorMessage;

	static Window& getInstance();

	bool initialize(HWND* hwnd, int sizeX, int sizeY);
	void shutdown();
	int getWidth();
	int getHeight();
protected:
	Window();
	Window(const Window&);
  ~Window(){};
  friend class DestroyerWindow;
private:
  static Window *_window;
  static DestroyerWindow _destroyer;

	int					_width;
	int					_height;
	HWND		    _hWnd;
	bool        _fullscreen;
};
