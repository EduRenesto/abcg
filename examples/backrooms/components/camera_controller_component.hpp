#ifndef __BACKROOMS_CAMERA_CONTROLLER_COMPONENT_HPP
#define __BACKROOMS_CAMERA_CONTROLLER_COMPONENT_HPP

#include <memory>

#include "../ecs.hpp"
#include "../rendering/camera.hpp"

struct CameraControllerComponent {
  ECS_DECLARE_TYPE

  std::shared_ptr<Camera> camera;
} __attribute__((aligned(16)));

#endif
