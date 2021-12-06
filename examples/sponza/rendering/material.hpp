#ifndef __SPONZA_MATERIAL_HPP
#define __SPONZA_MATERIAL_HPP

#include <string>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <fmt/format.h>

class Material {
public:
  Material(std::string tex_name, float shininess) :
    m_texture_name(tex_name),
    m_shininess(shininess) {}

  [[nodiscard]]
  const std::string& get_texture_name() const noexcept;

  [[nodiscard]]
  float get_shininess() const noexcept;

private:
  std::string m_texture_name;

  float m_shininess;
};

#endif
