#include "Camera.h"

Camera::Camera() {
  _viewMatrix = XMMatrixIdentity();
  _position = XMFLOAT3(10.0f, 20.0f, 10.0f);
  _look = XMFLOAT3(0.0f, -1.0f, 0.0f);
  _up = XMFLOAT3(0.0f, 0.0f, 1.0f);
  _right = XMFLOAT3(1.0f, 0.0f, 0.0f);
}
void Camera::shutdown() {
}
XMMATRIX& Camera::getViewMatrix() {
  return _viewMatrix;
}
XMFLOAT3* Camera::getPosition() {
  return &_position;
}
XMFLOAT3* Camera::getLook() {
  return &_look;
}
void Camera::pitch(float angle) {
  XMMATRIX t_ = XMMatrixRotationAxis(XMLoadFloat3(&_right), angle);
  XMStoreFloat3(&_up, XMVector3TransformCoord(XMLoadFloat3(&_up), t_));

  if(_up.y >= 0)
    XMStoreFloat3(&_look, XMVector3TransformCoord(XMLoadFloat3(&_look), t_));
}
void Camera::yaw(float angle) {
  XMMATRIX t_ = XMMatrixRotationY(angle);
  XMStoreFloat3(&_right, XMVector3TransformCoord(XMLoadFloat3(&_right), t_));
  XMStoreFloat3(&_look, XMVector3TransformCoord(XMLoadFloat3(&_look), t_));
}
void Camera::walk(float units) {
  _position.x += _look.x*units;
  _position.y += _look.y*units;
  _position.z += _look.z*units;
}
void Camera::strafe(float units) {
  _position.x += _right.x*units;
  _position.y += _right.y*units;
  _position.z += _right.z*units;
}
void Camera::update() {
  XMVECTOR look_ = XMVector3Normalize(XMLoadFloat3(&_look));
  XMStoreFloat3(&_look, look_);
  XMVECTOR up_ = XMVector3Cross(look_, XMLoadFloat3(&_right));
  up_ = XMVector3Normalize(up_);
  XMStoreFloat3(&_up, up_);
  XMVECTOR right_ = XMVector3Cross(up_, look_);
  right_ = XMVector3Normalize(right_);
  XMStoreFloat3(&_right, right_);

  float x;
  XMStoreFloat(&x, XMVector3Dot(XMLoadFloat3(&_right), XMLoadFloat3(&_position))); x = -x;
  float y;
  XMStoreFloat(&y, XMVector3Dot(XMLoadFloat3(&_up), XMLoadFloat3(&_position))); y = -y;
  float z;
  XMStoreFloat(&z, XMVector3Dot(XMLoadFloat3(&_look), XMLoadFloat3(&_position))); z = -z;

  _viewMatrix._11 = _right.x; _viewMatrix._12 = _up.x;
  _viewMatrix._21 = _right.y; _viewMatrix._22 = _up.y;
  _viewMatrix._31 = _right.z; _viewMatrix._32 = _up.z;
  _viewMatrix._41 = x;				_viewMatrix._42 = y;

  _viewMatrix._13 = _look.x; _viewMatrix._14 = 0.0f;
  _viewMatrix._23 = _look.y; _viewMatrix._24 = 0.0f;
  _viewMatrix._33 = _look.z; _viewMatrix._34 = 0.0f;
  _viewMatrix._43 = z;			 _viewMatrix._44 = 1.0f;
}
void Camera::setPosition(XMFLOAT3& pos) {
  _position = pos;
}
void Camera::setLook(XMFLOAT3& look) {
  _look = look;
}