#include "Entity.h"

#pragma region Entity
  Entity::Entity() {
    _worldMatrix = new XMFLOAT4X4();
    XMStoreFloat4x4(_worldMatrix, XMMatrixIdentity());

    _position = XMFLOAT3(0.0f, 0.0f, 0.0f);
    _scaling = XMFLOAT3(1.0f, 1.0f, 1.0f);
    _rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
    _modelName = "";
  }
  Entity::~Entity() {
    delete _worldMatrix;
  }
  void Entity::setModelName(string name) {
    _modelName = name;
  }
  string& Entity::getModelName() {
    return _modelName;
  }
  void Entity::update() {
  }
  void Entity::updateTransform() {
    XMStoreFloat4x4(_worldMatrix, XMMatrixMultiply(XMMatrixMultiply(
      XMMatrixScaling(_scaling.x, _scaling.y, _scaling.z),
      XMMatrixRotationRollPitchYaw(_rotation.x*PI_180, _rotation.y*PI_180, _rotation.z*PI_180)),
      XMMatrixTranslation(_position.x, _position.y, _position.z)));
  }
  void Entity::setPosition(XMFLOAT3& position) {
    _position = position;
  }
  void Entity::setScaling(XMFLOAT3& scale) {
    _scaling = scale;
  }
  void Entity::setRotation(XMFLOAT3& rotation) {
    _rotation = rotation;
  }
  XMFLOAT4X4* Entity::getWorldMatrix() {
    return _worldMatrix;
  }
  XMFLOAT3* Entity::getPosition() {
    return &_position;
  }
  XMFLOAT3* Entity::getScale() {
    return &_scaling;
  }
  XMFLOAT3* Entity::getRotation() {
    return &_rotation;
  }
#pragma endregion
#pragma region Player
  Player::Player() {
    // TODO: smooth transition to new cameraStyle
    _speed = 1.0f;
    _target = 0; 
  }
  Player::~Player() {

  }
  void Player::setTarger(Entity* entity) {
    _target = entity;
  }
  FirstPersonPlayer::FirstPersonPlayer() {
    // TODO: smooth transition to new cameraStyle
    _speed = 1.0f;
  }
  FirstPersonPlayer::~FirstPersonPlayer() {

  }
  RedactorPlayer::RedactorPlayer() {
    // TODO: smooth transition to new cameraStyle
    _speed = 1.0f;
  }
  RedactorPlayer::~RedactorPlayer() {

  }
  void Player::update() {
    // TODO: When TerrainManager will be exist - rewrite this code
    // WASD walk&strafe on terrainHeight & camera goes to look at player
    // update _worldMatrix, mouseDrug - cameraMove, leftMouseClick - create point to go on terrain
    // rightMouseClick - tips?
    if(_target) {
      XMFLOAT3 targetPos_ = 
        XMFLOAT3(_target->getWorldMatrix()->_41, _target->getWorldMatrix()->_42 + 20.0f, _target->getWorldMatrix()->_43);
      Camera::getInstance().setPosition(targetPos_);
    }
  }
  void FirstPersonPlayer::update() {
    float delta = _speed;
    if(Input::getInstance().LShift()) delta *= 4.0f;
    if(Input::getInstance().W()) Camera::getInstance().walk(1.1f * delta);
    if(Input::getInstance().S()) Camera::getInstance().walk(-1.1f * delta);
    if(Input::getInstance().D()) Camera::getInstance().strafe(1.1f * delta);
    if(Input::getInstance().A()) Camera::getInstance().strafe(-1.1f * delta);
    Camera::getInstance().yaw(Input::getInstance().MouseX());
    Camera::getInstance().pitch(Input::getInstance().MouseY());
  }
  void RedactorPlayer::update() {
    float delta = _speed;
    if(Input::getInstance().LShift()) delta *= 8.0f;
    if(Input::getInstance().LControl()) {
      Camera::getInstance().yaw(Input::getInstance().MouseX());
      Camera::getInstance().pitch(Input::getInstance().MouseY());
    }
    Camera::getInstance().walk(Input::getInstance().MouseZ() * delta);
  }
#pragma endregion