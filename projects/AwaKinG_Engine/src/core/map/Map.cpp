#include "Map.h"

Map::Map() {
	errorMessage = ED_UNDEFINED;
  _cameraManager = new FirstPersonPlayer();
}
void Map::shutdown() {
	for(uint i = 0; i < _entities.size(); i++)
		delete _entities[i];
	_entities.clear();
}
void Map::update() {
  _cameraManager->update();
  for(uint i = 0; i < _entities.size(); i++)
    _entities[i]->update();
}
bool Map::initialize() {

	return true;
}
void Map::addEntity(Entity* entity) {
  _entities.push_back(entity);
}
void Map::setCameraType(PlayerCameraType type) {
  switch(type) {
  case PCT_FIRST_PERSON:
    _cameraManager = new FirstPersonPlayer();
    break;
  case PCT_REDACTOR:
    _cameraManager = new RedactorPlayer();
    break;
  case PCT_GAME:
    _cameraManager = new Player();
    break;
  default:
    break;
  }
}
