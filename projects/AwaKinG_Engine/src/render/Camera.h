#ifndef __CAMERA_H
#define __CAMERA_H

#include "Additional.h"

class Camera {
public:
  static Camera& getInstance() {
    static Camera camera_;
    return camera_;
  }
  XMMATRIX& getViewMatrix();
private:
  Camera();
  Camera(const Camera&);

  XMMATRIX _viewMatrix;
};

#endif
