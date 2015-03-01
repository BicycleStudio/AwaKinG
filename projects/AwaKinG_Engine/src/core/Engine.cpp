#include "Engine.h"

Engine::Engine(){
	errorMessage = ED_UNDEFINED;
	_active = false;
}
bool Engine::initialize(){
	_active = true;

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
}
