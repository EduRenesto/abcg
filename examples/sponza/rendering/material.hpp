#ifndef __SPONZA_MATERIAL_HPP
#define __SPONZA_MATERIAL_HPP

#include <string>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class Material {
public:
  explicit Material(std::string tex_name) : m_texture_name(std::move(tex_name)) {}

  [[nodiscard]]
  const std::string& get_texture_name() const noexcept;

private:
  std::string m_texture_name;
};

#endif
