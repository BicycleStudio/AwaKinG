#include "Map.h"

Map::Map() {
	errorMessage = ED_UNDEFINED;
  _cameraManager = 0;
}
void Map::_clear() {
  Render::getInstance().clear();
  for(uint i = 0; i < _entities.size(); i++)
    delete _entities[i];
  _entities.clear();
}
void Map::shutdown() {
  _clear();
  if(_cameraManager)
    delete _cameraManager;
}
void Map::update() {
  _cameraManager->update();
  for(uint i = 0; i < _entities.size(); i++)
    _entities[i]->update();
}
bool Map::initialize() {
  shutdown();
  _cameraManager = new RedactorPlayer();
	return true;
}
bool Map::initialize(string fileName) {
  shutdown();
  _cameraManager = new RedactorPlayer();
  OPEN_STREAM(fileName, "r");

  int countEntity_ = 0; 
  READ_INT(&countEntity_);

  for(int i = 0; i < countEntity_; i++)  {
    char* entityName_ = new char[255];
    XMFLOAT3 pos_; XMFLOAT3 scl_; XMFLOAT3 rot_;
    READ_STRING(&entityName_);
    READ_FLOAT(&pos_.x); READ_FLOAT(&pos_.y); READ_FLOAT(&pos_.z);
    READ_FLOAT(&scl_.x); READ_FLOAT(&scl_.y); READ_FLOAT(&scl_.z);
    READ_FLOAT(&rot_.x); READ_FLOAT(&rot_.y); READ_FLOAT(&rot_.z);

    Entity* entity_ = new Entity();
    entity_->setModelName(entityName_);
    entity_->setPosition(pos_);
    entity_->setScaling(scl_);
    entity_->setRotation(rot_);
    entity_->updateTransform();
    _entities.push_back(entity_);

    Render::getInstance().addModel(entityName_, entity_->getWorldMatrix());
  }

  CLOSE_STREAM();
  return true;
}
bool Map::initializeTestScene1() {
  shutdown();
  _cameraManager = new RedactorPlayer();
  Entity *ent = new Entity();
  _entities.push_back(ent);
  ent->setPosition(XMFLOAT3(0.0f, 5.0f, 0.0f));
  ent->updateTransform();
  if(!Render::getInstance().createTestTri(ent->getWorldMatrix())) return false; 

  Player* player_ = new Player();
  player_->setTarger(ent);
  delete _cameraManager;
  _cameraManager = player_;

  Entity *ent2 = new Entity();
  ent2->setPosition(XMFLOAT3(-10.0f,5.0f,0.0f));
  ent2->updateTransform();
  _entities.push_back(ent2);
  return Render::getInstance().createTestTri(ent2->getWorldMatrix());
}
void Map::addEntity(Entity* entity) {
  _entities.push_back(entity);
}
void Map::setCameraType(PlayerCameraType type) {
  switch(type) {
  case PCT_FIRST_PERSON_FREE:
    delete _cameraManager;
    _cameraManager = new FirstPersonFreePlayer();
    break;
  case PCT_FIRST_PERSON:
    delete _cameraManager;
    _cameraManager = new FirstPersonPlayer();
    break;
  case PCT_REDACTOR:
    delete _cameraManager;
    _cameraManager = new RedactorPlayer();
    break;
  case PCT_GAME:
  {
    Player* player_ = new Player();
    // TODO: Link to some entity!
    if(_entities.size()!=0) player_->setTarger(_entities[0]);
    delete _cameraManager;
    _cameraManager = player_;
    break;
  }
  default:
    break;
  }
}
bool Map::save(string fileName) {
  OPEN_STREAM(fileName, "w");
  WRITE_INT(_entities.size());
  Parser::getInstance().newLine();

  for(uint i = 0; i < _entities.size(); i++) {
    WRITE_STRING(_entities[i]->getModelName().c_str(), _entities[i]->getModelName().length());
    Parser::getInstance().newLine();
    WRITE_FLOAT(_entities[i]->getPosition()->x); WRITE_FLOAT(_entities[i]->getPosition()->y); WRITE_FLOAT(_entities[i]->getPosition()->z);
    WRITE_FLOAT(_entities[i]->getScale()->x); WRITE_FLOAT(_entities[i]->getScale()->y); WRITE_FLOAT(_entities[i]->getScale()->z);
    WRITE_FLOAT(_entities[i]->getRotation()->x); WRITE_FLOAT(_entities[i]->getRotation()->y); WRITE_FLOAT(_entities[i]->getRotation()->z);
    Parser::getInstance().newLine();
  }
  CLOSE_STREAM();

  Terrain::getInstance().save(fileName);

  return true;
}