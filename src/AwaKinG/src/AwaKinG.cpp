#include "Window.h"
#include "../../AwaKinG_Engine/src/AwaKing_Engine.h"
#pragma comment(lib, "../../Lib/AwaKinG_Engine.lib")

#define _ITERATOR_DEBUG_LEVEL 0

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define tryInit(obj) if(!obj->initialize(&gHwnd,SCREEN_WIDTH,SCREEN_HEIGHT)){MessageBox(NULL, obj->ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR);shutdown();return 1;}

HWND gHwnd;
Window* gWindow = 0;
RedactorEngine* gEngine = 0;
bool gMinimized = false;
bool gEngineInitialized = false;

void messageLoop();
void shutdown();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR	lpCmdLine, int	nCmdShow)
{
	gWindow = &Window::getInstance();
	tryInit(gWindow);

	gEngine = new RedactorEngine();//&Engine::getInstance();
	gEngine->setShortPaths();
	if(!gEngine->initialize(gHwnd, gHwnd, gWindow->getWidth(), gWindow->getHeight()))
	{
		MessageBox(NULL, gEngine->ErrorMessage.c_str(), "initialize error", MB_OK | MB_ICONERROR);
		shutdown();
		return 1;
	}
	gEngineInitialized = true;

	gEngine->setTerrainWireframe(false);
	gEngine->createTerrain(1, 1);
	gEngine->diamondSquareTerrain();
	//gEngine->randomizeTerrain(1);

	gEngine->setCameraManagerType(Engine::CameraManagerType::CMT_REDACTORFREE);
	//gEngine->loadTerrain("../../resources/map/terrain/DK2.ter");

	//gEngine->createMapFromFile("../../resources/map/winterfell.map");

	gEngine->setActive(true);
	messageLoop();

	shutdown();
	return 0;
}
void shutdown()
{
	gEngine->shutdown();
	gWindow->shutdown();
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
		if(gEngineInitialized)
		{
			if(gEngine->active())
				gEngine->resizeRenderBuffer(LOWORD(lParam), HIWORD(lParam));
		}
		return 0;
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