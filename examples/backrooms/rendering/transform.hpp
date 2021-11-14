#ifndef __BACKROOMS_TRANSFORM_HPP
#define __BACKROOMS_TRANSFORM_HPP

#include <glm/glm.hpp>

class Transform {
public:
  Transform() = default;

  glm::mat4 build_model_matrix();

private:
  glm::vec3 position{};
};

#endif
