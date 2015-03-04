#include "Camera.h"

Camera::Camera() {
  _viewMatrix = XMMatrixIdentity();
}
XMMATRIX& Camera::getViewMatrix() {
  return _viewMatrix;
}
