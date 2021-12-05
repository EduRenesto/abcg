#ifndef __SPONZA_LIGHT_HPP
#define __SPONZA_LIGHT_HPP

#include <glm/glm.hpp>

class Light {
public:
  Light(glm::vec3 position, glm::vec3 color) : m_position(position), m_color(color) {}

private:
  glm::vec3 m_position;
  glm::vec3 m_color;
};

#endif
