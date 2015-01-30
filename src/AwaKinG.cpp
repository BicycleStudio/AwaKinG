#include "Window.h"
#include "core/Engine.h"

Window* gWindow = 0;
Engine* gEngine = 0;

#define tryInit(obj) if(!obj->initialize()){MessageBox(NULL, obj->ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR);shutdown();return 1;}

void shutdown();
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR	lpCmdLine, int	nCmdShow) 
{
	gWindow = &Window::getInstance(); 
	tryInit(gWindow);
	gEngine = &Engine::getInstance();
	int width; int height;
	HWND hwnd = gWindow->getWindow(&width, &height);
	gEngine->setInitialize(hwnd, width, height);
	tryInit(gEngine);

	shutdown();
	return 0;
}
void shutdown()
{
	safeRelease(gEngine);
	safeRelease(gWindow);
}
LRESULT CALLBACK WndProc(HWND	hWnd, UINT	uMsg, WPARAM	wParam, LPARAM	lParam)			// Additional Message Information
{
	switch(uMsg) 
	{
		case WM_ACTIVATE:	
		{
			return 0;
		}
		case WM_SYSCOMMAND:	
		{
			switch(wParam) 
			{
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

		case WM_KEYDOWN: 
		{
			//gWindow->setKey(wParam, true);
			return 0;
		}

		case WM_KEYUP: 
		{
			//gWindow->setKey(wParam, false);
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