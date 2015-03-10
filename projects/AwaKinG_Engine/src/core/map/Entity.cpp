#include "Entity.h"
#include "Terrain.h"

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
  void Entity::updateTranslation() {
    _worldMatrix->_41 = _position.x;
    _worldMatrix->_42 = _position.y;
    _worldMatrix->_43 = _position.z;
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
    _up = XMFLOAT3(0.0f, 1.0f, 0.0f);
    _distanceToCamera = 20.0f;
  }
  Player::~Player() {

  }
  void Player::setTarger(Entity* entity) {
    _target = entity;
    _look = XMFLOAT3(0.0f,0.0f,1.0f);
    Camera::getInstance().setPosition(
      XMFLOAT3(_target->getPosition()->x + Camera::getInstance().getLook()->x*_distanceToCamera, 
      _target->getPosition()->y + Camera::getInstance().getLook()->y*_distanceToCamera,
      _target->getPosition()->z + Camera::getInstance().getLook()->z*_distanceToCamera));
  }
  FirstPersonFreePlayer::FirstPersonFreePlayer() {
    // TODO: smooth transition to new cameraStyle
    _speed = 1.0f;
  }
  FirstPersonFreePlayer::~FirstPersonFreePlayer() {

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
    _distanceToCamera += (Input::getInstance().MouseZ() * _speed);
    if(_distanceToCamera < 20.0f) _distanceToCamera = 20.0f;
    if(_distanceToCamera > 100.0f) _distanceToCamera = 100.0f;
    
    if(_target) {
      XMFLOAT3* pos = _target->getPosition();

      XMVECTOR right_ = XMVector3Cross(XMLoadFloat3(&_up), XMLoadFloat3(&_look));
      right_ = XMVector3Normalize(right_);
      XMStoreFloat3(&_right, right_);

      if(Input::getInstance().D()) strafe(_speed / 10.0f);
      if(Input::getInstance().A()) strafe(-_speed / 10.0f);
      if(Input::getInstance().W()) walk(pos, _speed);
      if(Input::getInstance().S()) walk(pos, -_speed);

      if(Terrain::getInstance().getInitialized())
        pos->y = Terrain::getInstance().getHeight(pos->x, pos->z);

      _target->updateTransform();

      Camera::getInstance().setPosition(
        XMFLOAT3(pos->x - _distanceToCamera*_look.x,
        pos->y + _distanceToCamera,
        pos->z - _distanceToCamera*_look.z));

      Camera::getInstance().yaw(Input::getInstance().MouseX());
      Camera::getInstance().pitch(Input::getInstance().MouseY());
    }
  }
  void Player::walk(XMFLOAT3* pos, float units) {
    pos->x += _look.x*units;
    pos->y += _look.y*units;
    pos->z += _look.z*units;
  }
  void Player::strafe(float units) {
    XMMATRIX t_ = XMMatrixRotationY(units);
    XMStoreFloat3(&_look, XMVector3TransformCoord(XMLoadFloat3(&_look), t_));

    XMFLOAT3* rot = _target->getRotation();
    rot->y += units/PI_180;
  }
  void FirstPersonFreePlayer::update() {
    float delta = _speed;
    if(Input::getInstance().LShift()) delta *= 4.0f;
    if(Input::getInstance().W()) Camera::getInstance().walk(1.1f * delta);
    if(Input::getInstance().S()) Camera::getInstance().walk(-1.1f * delta);
    if(Input::getInstance().D()) Camera::getInstance().strafe(1.1f * delta);
    if(Input::getInstance().A()) Camera::getInstance().strafe(-1.1f * delta);
    Camera::getInstance().yaw(Input::getInstance().MouseX());
    Camera::getInstance().pitch(Input::getInstance().MouseY());
  }
  void FirstPersonPlayer::update() {
    float delta = _speed;
    if(Input::getInstance().LShift()) delta *= 4.0f;
    if(Input::getInstance().W()) Camera::getInstance().walk(1.1f * delta);
    if(Input::getInstance().S()) Camera::getInstance().walk(-1.1f * delta);
    if(Input::getInstance().D()) Camera::getInstance().strafe(1.1f * delta);
    if(Input::getInstance().A()) Camera::getInstance().strafe(-1.1f * delta);

    if(Terrain::getInstance().getInitialized()) {
      XMFLOAT3* pointer_ = Camera::getInstance().getPosition();
      pointer_->y = Terrain::getInstance().getHeight(pointer_->x, pointer_->z) + 5.0f;
    }
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