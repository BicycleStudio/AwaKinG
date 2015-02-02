#include "Window.h"
#include "core/Engine.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

HWND gHwnd;
Window* gWindow = 0;
Engine* gEngine = 0;
bool gMinimized = false;

#define tryInit(obj) if(!obj->initialize(&gHwnd,SCREEN_WIDTH,SCREEN_HEIGHT)){MessageBox(NULL, obj->ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR);shutdown();return 1;}

void messageLoop();
void shutdown();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR	lpCmdLine, int	nCmdShow) 
{
	gWindow = &Window::getInstance(); 
	tryInit(gWindow);

	gEngine = &Engine::getInstance();
	tryInit(gEngine);

	messageLoop();

	shutdown();
	return 0;
}
void shutdown()
{
	safeShutdown(gEngine);
	safeShutdown(gWindow);
}
LRESULT CALLBACK WndProc(HWND	hWnd, UINT	uMsg, WPARAM	wParam, LPARAM	lParam)			// Additional Message Information
{
	switch(uMsg) 
	{
		case WM_ACTIVATE:
		{
			if(!gMinimized)
			{
				if(wParam)
				{
					if(gEngine)gEngine->setActive(true);
				}
				else
				{
					if(gEngine)gEngine->setActive(false);
				}
				return 0;
			}
		}
		case WM_SYSCOMMAND:	
		{
			switch(wParam) 
			{
			case SC_MINIMIZE:
				gMinimized = true;
				if(gEngine)gEngine->setActive(false);
				break;
			case 1:
				gMinimized = false;
				if(gEngine)gEngine->setActive(true);
				break;
			case SC_SCREENSAVE:
				return 0;
			case SC_MONITORPOWER:
				return 0;
			}
			break;
		}
		case WM_CLOSE: 
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_SIZE: 
		{
			//gWindow->resizeScene(LOWORD(lParam), HIWORD(lParam));
			return 0;
		}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void messageLoop()
{
	MSG msg_;
	bool done_ = false;
	while(!done_)
	{
		if(PeekMessage(&msg_, NULL, 0, 0, PM_REMOVE))
		{
			if(msg_.message == WM_QUIT)
				done_ = true;
			else
			{
				TranslateMessage(&msg_);
				DispatchMessage(&msg_);
			}
		}
		else
		{
			if(gEngine->active())
				done_ = gEngine->update();
		}
	}
}