#ifndef __SPONZA_LIGHT_HPP
#define __SPONZA_LIGHT_HPP

#include <glm/glm.hpp>
#include <optional>

class Light {
public:
  Light(glm::vec3 position, glm::vec3 direction);

  [[nodiscard]]
  glm::mat4 get_matrix() const;

private:
  glm::vec3 m_position;
  glm::vec3 m_direction;

  glm::mat4 m_matrix{};
};

#endif
