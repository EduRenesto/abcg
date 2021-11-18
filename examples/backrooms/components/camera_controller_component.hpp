#ifndef __BACKROOMS_CAMERA_CONTROLLER_COMPONENT_HPP
#define __BACKROOMS_CAMERA_CONTROLLER_COMPONENT_HPP

#include <memory>

#include "../ecs.hpp"
#include "../rendering/camera.hpp"

struct CameraControllerComponent {
  ECS_DECLARE_TYPE

  std::shared_ptr<Camera> camera;

  glm::vec3 eye;
  glm::vec3 center;
  glm::vec3 up;
} __attribute__((aligned(64)));

ECS_DEFINE_TYPE(CameraControllerComponent)

#endif
