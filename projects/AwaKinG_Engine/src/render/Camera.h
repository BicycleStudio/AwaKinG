#ifndef __CAMERA_H
#define __CAMERA_H

#include "Additional.h"

class Camera {
public:
  static Camera& getInstance() {
    static Camera cam_;
    return cam_;
  }
  XMMATRIX& getViewMatrix();
  void shutdown();
  void update();
  XMFLOAT3* getPosition();
  XMFLOAT3* getLook();

  void yaw(float angle);
  void pitch(float angle);
  void walk(float units);
  void strafe(float units);
protected:
  Camera();
  Camera(const Camera&);

  XMMATRIX _viewMatrix;
  XMFLOAT3 _position;
  XMFLOAT3 _look;
  XMFLOAT3 _up;
  XMFLOAT3 _right;
};
#endif
