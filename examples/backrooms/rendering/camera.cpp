#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Camera::build_view_matrix() const {
  return glm::lookAt(this->m_eye, this->m_center, this->m_up);
}
