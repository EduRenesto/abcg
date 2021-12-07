#include "light.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Light::Light(
  glm::vec3 position,
  glm::vec3 direction
) : m_position(position), m_direction(direction) {
  //auto SIZE{20.0f};
  auto view{glm::lookAt(position, direction, glm::vec3(0.0f, 1.0f, 0.0f))};
  //auto projection{glm::ortho(-SIZE, SIZE, -SIZE, SIZE, 1.0f, 750.0f)};
  auto projection{glm::perspective((float) M_PI / 2.0f, 1.0f, 1.0f, 750.0f)};

  this->m_matrix = projection * view;
}

glm::mat4 Light::get_matrix() const {
  return this->m_matrix;
}
