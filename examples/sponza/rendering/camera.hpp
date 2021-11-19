#ifndef __SPONZA_CAMERA_HPP
#define __SPONZA_CAMERA_HPP

#include <glm/glm.hpp>

class Camera {
public:
  Camera() = default;

  Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up) :
    m_eye(eye),
    m_center(center),
    m_up(up)
  {};

  [[nodiscard]]
  glm::mat4 build_view_matrix() const;

  void set_eye(glm::vec3 eye);
  void set_center(glm::vec3 center);
  void set_up(glm::vec3 up);

private:
  glm::vec3 m_eye{};
  glm::vec3 m_center{};
  glm::vec3 m_up{};
};

#endif
