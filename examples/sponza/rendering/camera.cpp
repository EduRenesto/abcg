#include "camera.hpp"

#include <fmt/format.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

glm::mat4 Camera::build_view_matrix() const {
  auto eye{glm::to_string(this->m_eye)};
  auto center{glm::to_string(this->m_center)};
  auto up{glm::to_string(this->m_up)};
  //fmt::print("Camera::build_view_matrix()\n");
  //fmt::print("\neye = {}, center = {}, up = {}\n", eye, center, up);
  return glm::lookAt(this->m_eye, this->m_center, this->m_up);
}

void Camera::set_up(glm::vec3 up) {
  //fmt::print("Camera::set_up({})\n", glm::to_string(up));
  this->m_up = up;
}

void Camera::set_eye(glm::vec3 eye) {
  //fmt::print("Camera::set_eye({})\n", glm::to_string(eye));
  this->m_eye = eye;
}

void Camera::set_center(glm::vec3 center) {
  //fmt::print("Camera::set_center({})\n", glm::to_string(center));
  this->m_center = center;
}

glm::vec3 Camera::get_center() const {
  return this->m_center;
}
