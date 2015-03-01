#include "EngineWrap.h"

EngineWrap::EngineWrap()
{
	_initialized = false;
	_active = false;
}
bool EngineWrap::initialize(HWND mainHwnd, HWND hwnd){
	if(!Render::getInstance().initialize(hwnd, 2000, 2000))
		OUTPUT_ERROR(Render::getInstance(), ED_RENDER);
	if(!Input::getInstance().initialize(mainHwnd)) 
		OUTPUT_ERROR(Input::getInstance(), ED_INPUT);
	if(!Engine::getInstance().initialize()) 
		OUTPUT_ERROR(Engine::getInstance(), ED_ENGINE);
	if(!Map::getInstance().initialize())
		OUTPUT_ERROR(Map::getInstance(), ED_MAP);
	_initialized = true;
	_active = true;
	setActive(_active);

	return true;
}
void EngineWrap::release(){
	Engine::getInstance().shutdown();
	Input::getInstance().shutdown();
	Render::getInstance().shutdown();
}
void EngineWrap::update(){
	if(Engine::getInstance().getActive()) {
		Input::getInstance().update();
		Engine::getInstance().update();
		Render::getInstance().update();
	}
}
void EngineWrap::setActive(bool value){
	_active = value;
	Engine::getInstance().setActive(value);
}
void EngineWrap::resizeBuffer(int sizeX, int sizeY){
	Render::getInstance().resizeBuffer(sizeX, sizeY);
}
bool EngineWrap::getInitialized(){
	return _initialized; 
}
bool EngineWrap::getActive(){
	return _active;
}