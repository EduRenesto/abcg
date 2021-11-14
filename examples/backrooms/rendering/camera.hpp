#ifndef __BACKROOMS_CAMERA_HPP
#define __BACKROOMS_CAMERA_HPP

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

private:
  glm::vec3 m_eye{};
  glm::vec3 m_center{};
  glm::vec3 m_up{};
};

#endif
