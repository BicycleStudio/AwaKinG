#include "Map.h"

Map::Map() {
	errorMessage = ED_UNDEFINED;
  _cameraManager = new Player();
}
void Map::_clear() {
  for(uint i = 0; i < _entities.size(); i++)
    delete _entities[i];
  _entities.clear();
}
void Map::shutdown() {
  _clear();
  delete _cameraManager;
}
void Map::update() {
  _cameraManager->update();
  for(uint i = 0; i < _entities.size(); i++)
    _entities[i]->update();
}
bool Map::initialize() {
	return true;
}
bool Map::initialize(string fileName) {
  //Parser::getInstance();
  return true;
}
bool Map::initializeTestScene1() {
  Entity *ent = new Entity();
  _entities.push_back(ent);
  if(!Render::getInstance().createTestTri(ent->getWorldMatrix())) return false; 

  Player* player_ = new Player();
  player_->setTarger(ent);
  delete _cameraManager;
  _cameraManager = player_;

  Entity *ent2 = new Entity();
  ent2->setPosition(XMFLOAT3(-10.0f,0.0f,0.0f));
  _entities.push_back(ent2);
  return Render::getInstance().createTestTri(ent2->getWorldMatrix());
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
  {
    Player* player_ = new Player();
    // TODO: Link to some entity!
    if(_entities.size()!=0)player_->setTarger(_entities[0]);
    delete _cameraManager;
    _cameraManager = player_;
    break;
  }
  default:
    break;
  }
}
