#include "Window.h"
#include "EngineWrap.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

bool gMinimized = false;

void messageLoop();
void shutdown();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR	lpCmdLine, int	nCmdShow) {
	HWND hwnd_;
	Window::getInstance().initialize(&hwnd_, SCREEN_WIDTH, SCREEN_HEIGHT);

	if(!EngineWrap::getInstance().initialize(hwnd_, hwnd_)) {
		MessageBox(NULL, "initialize", "initialize error", MB_OK | MB_ICONERROR);
		shutdown();
		return 1;
	}
  EngineWrap::getInstance().resizeBuffer(Window::getInstance().getWidth(), Window::getInstance().getHeight());
  Map::getInstance().initialize("../../resources/map/testMap2.amp");
  Map::getInstance().setCameraType(PCT_GAME);
  Terrain::getInstance().create(1, 1);
  Terrain::getInstance().getHeight(1, 1);
  messageLoop();

	shutdown();
	return 0;
}
void shutdown() {
	EngineWrap::getInstance().release();
	Window::getInstance().shutdown();
}
LRESULT CALLBACK WndProc(HWND	hWnd, UINT	uMsg, WPARAM	wParam, LPARAM	lParam)			// Additional Message Information
{
	switch(uMsg) {
	case WM_ACTIVATE:
	{
		if(!gMinimized) {
			if(wParam) {
				EngineWrap::getInstance().setActive(true);
			}
			else {
				EngineWrap::getInstance().setActive(false);
			}
			return 0;
		}
	}
	case WM_SYSCOMMAND:
	{
		switch(wParam) {
		case SC_MINIMIZE:
			gMinimized = true;
			EngineWrap::getInstance().setActive(false);
			break;
		case 1:
			gMinimized = false;
			EngineWrap::getInstance().setActive(true);
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
		if(EngineWrap::getInstance().getInitialized()) {
      if(EngineWrap::getInstance().getActive())
				EngineWrap::getInstance().resizeBuffer(LOWORD(lParam), HIWORD(lParam));
    }
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void messageLoop() {
	MSG msg_;
	bool done_ = false;
	while(!done_) {
		if(PeekMessage(&msg_, NULL, 0, 0, PM_REMOVE)) {
			if(msg_.message == WM_QUIT)
				done_ = true;
			else {
				TranslateMessage(&msg_);
				DispatchMessage(&msg_);
			}
		}
		else {
			EngineWrap::getInstance().update();
		}
	}
}