#include "transform.hpp"
#include <glm/ext/matrix_transform.hpp>

glm::mat4 Transform::build_model_matrix() {
  glm::mat4 model{1.0};

  model = glm::translate(model, this->m_position);
  model = glm::scale(model, this->m_scale);

  return model;
}
