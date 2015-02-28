#include "AwaKinG_Engine.h"

bool initialize(HWND mainHwnd, HWND hwnd){
	if (!Render::getInstance()->initialize(hwnd, 2000, 2000)) return false;
	if (!Input::getInstance()->initialize(mainHwnd)) return false;
	if(!Engine::getInstance()->initialize()) return false;
	if(!Map::getInstance()->initialize()) return false;

	return true;
}
void release(){
	Map::getInstance()->shutdown();
	Engine::getInstance()->shutdown();
	Input::getInstance()->shutdown();
	Render::getInstance()->shutdown();
}
void update(){
	if(Engine::getInstance()->getActive()){
		Input::getInstance()->update();
		Map::getInstance()->update();
		Engine::getInstance()->update();
		Render::getInstance()->update();
	}
}
void setActive(bool value){
	Engine::getInstance()->setActive(value);
}
void resizeBuffer(int sizeX, int sizeY){
	Render::getInstance()->resizeBuffer(sizeX, sizeY);
}
