#ifndef __BACKROOMS_TRANSFORM_HPP
#define __BACKROOMS_TRANSFORM_HPP

#include <glm/glm.hpp>

class Transform {
public:
  Transform() = default;
  Transform(glm::vec3 position, glm::vec3 scale) :
    m_position(position),
    m_scale(scale)
  {}

  glm::mat4 build_model_matrix();

private:
  glm::vec3 m_position{};
  glm::vec3 m_scale{1.0};
};

#endif
