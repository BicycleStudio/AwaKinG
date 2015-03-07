#include "Entity.h"

#pragma region Entity
  Entity::Entity() {
    _worldMatrix = new XMFLOAT4X4();
    XMStoreFloat4x4(_worldMatrix, XMMatrixIdentity());

    _position = XMFLOAT3(0.0f, 0.0f, 0.0f);
    _scaling = XMFLOAT3(1.0f, 1.0f, 1.0f);
    _rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
  }
  Entity::~Entity() {
    delete _worldMatrix;
  }
  void Entity::update() {
    _position.x += 0.1f;
    updateTransform();
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
#pragma endregion
#pragma region Player
  Player::Player() {
    // TODO: smooth transition to new cameraStyle
    _target = 0;
  }
  Player::~Player() {

  }
  void Player::setTarger(Entity* entity) {
    _target = entity;
  }
  FirstPersonPlayer::FirstPersonPlayer() {
    // TODO: smooth transition to new cameraStyle
  }
  FirstPersonPlayer::~FirstPersonPlayer() {

  }
  RedactorPlayer::RedactorPlayer() {
    // TODO: smooth transition to new cameraStyle
  }
  RedactorPlayer::~RedactorPlayer() {

  }
  void Player::update() {
    // TODO: When inputClass will be exist - write this code
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
    // TODO: When inputClass will be exist - rewrite this code
    // WASD walk&strafe, mouseDrug - look around.
    Camera::getInstance().walk(0.1f);
  }
  void RedactorPlayer::update() {
    // TODO: When inputClass will be exist - rewrite this code
    // MouseWheele walk, no strafe, LeftCTRL+mouseDrug - look around.
    // MouseWheele click and mouseDrug - rotation around point
    Camera::getInstance().walk(-0.1f);
  }
#pragma endregion