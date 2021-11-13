#ifndef __BACKROOMS_TRANSFORM_HPP
#define __BACKROOMS_TRANSFORM_HPP

#include <glm/glm.hpp>
#include "../ecs.hpp"

class Transform {
  ECS_DECLARE_TYPE

public:
  Transform() = default;

  glm::vec3 position{};
};

ECS_DEFINE_TYPE(Transform)

#endif
