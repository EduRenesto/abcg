#ifndef __SPONZA_MESH_HPP
#define __SPONZA_MESH_HPP

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "material.hpp"

class Mesh {
public:
  Mesh(
       std::string name,
       std::vector<glm::vec3> positions,
       std::vector<glm::vec3> normals,
       std::vector<glm::vec2> tex_coords,
       Material material
  ) :
    m_name(name),
    m_positions(std::move(positions)),
    m_normals(std::move(normals)),
    m_tex_coords(std::move(tex_coords)),
    m_material(std::move(material))
  {}

  [[nodiscard]]
  const std::string& get_name() const noexcept;

  [[nodiscard]]
  const std::vector<glm::vec3>& get_positions() const noexcept;

  [[nodiscard]]
  const std::vector<glm::vec3>& get_normals() const noexcept;

  [[nodiscard]]
  const std::vector<glm::vec2>& get_tex_coords() const noexcept;

  [[nodiscard]]
  const Material& get_material() const noexcept;

private:
  std::string m_name;

  std::vector<glm::vec3> m_positions;
  std::vector<glm::vec3> m_normals;
  std::vector<glm::vec2> m_tex_coords;

  Material m_material;
};

#endif
