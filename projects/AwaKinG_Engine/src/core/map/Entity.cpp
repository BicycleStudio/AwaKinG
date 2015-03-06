#include "Entity.h"

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