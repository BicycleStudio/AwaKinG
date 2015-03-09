#include "Engine.h"

Engine::Engine(){
	errorMessage = ED_UNDEFINED;
	_active = false;
  _initialized = false;
}
bool Engine::initialize(){
	_active = true;
  _initialized = true;
	return true;
}
void Engine::shutdown(){

}
void Engine::update(){

}
bool Engine::getActive(){
	return _active;
}
void Engine::setActive(bool value){
	_active = value;
  if(_active && _initialized)
    Input::getInstance().acquire();
}
