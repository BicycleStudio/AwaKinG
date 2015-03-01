#include "EngineWrap.h"

EngineWrap *EngineWrap::_engine = 0;
DestroyerEngineWrap EngineWrap::_destroyer;

DestroyerEngineWrap::~DestroyerEngineWrap(){
  delete _engine;
}
void DestroyerEngineWrap::initialize(EngineWrap *engine){
  _engine = engine;
}

EngineWrap& EngineWrap::getInstance(){
  if(!_engine){
		_engine = new EngineWrap();
    _destroyer.initialize(_engine);
	}
	return *_engine;
}
EngineWrap::EngineWrap()
{
	_initialized = false;
	_active = false;
}
bool EngineWrap::initialize(HWND mainHwnd, HWND hwnd){
	if(!Render::getInstance()->initialize(hwnd, 2000, 2000)) return false;
	if(!Input::getInstance()->initialize(mainHwnd)) return false;
	if(!Engine::getInstance()->initialize()) return false;

	_initialized = true;
	_active = true;
	setActive(_active);

	return true;
}
void EngineWrap::release(){
	Engine::getInstance()->shutdown();
	Input::getInstance()->shutdown();
	Render::getInstance()->shutdown();
}
void EngineWrap::update(){
	if(Engine::getInstance()->getActive()){
		Input::getInstance()->update();
		Engine::getInstance()->update();
		Render::getInstance()->update();
	}
}
void EngineWrap::setActive(bool value){
	_active = value;
	Engine::getInstance()->setActive(value);
}
void EngineWrap::resizeBuffer(int sizeX, int sizeY){
	Render::getInstance()->resizeBuffer(sizeX, sizeY);
}
bool EngineWrap::getInitialized(){
	return _initialized; 
}
bool EngineWrap::getActive(){
	return _active;
}