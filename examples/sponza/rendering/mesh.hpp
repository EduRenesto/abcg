#ifndef __SPONZA_MESH_HPP
#define __SPONZA_MESH_HPP

#include <glm/glm.hpp>
#include <vector>

#include "material.hpp"

class Mesh {
public:
  Mesh(
       std::vector<glm::vec3> positions,
       std::vector<glm::vec3> normals,
       std::vector<glm::vec2> tex_coords,
       std::vector<int> material_indices,
       std::vector<Material> materials
  ) :
    m_positions(std::move(positions)),
    m_normals(std::move(normals)),
    m_tex_coords(std::move(tex_coords)),
    m_material_indices(std::move(material_indices)),
    m_materials(std::move(materials))
  {}

  [[nodiscard]]
  const std::vector<glm::vec3>& get_positions() const noexcept;

  [[nodiscard]]
  const std::vector<glm::vec3>& get_normals() const noexcept;

  [[nodiscard]]
  const std::vector<glm::vec2>& get_tex_coords() const noexcept;

  [[nodiscard]]
  const std::vector<int>& get_material_indices() const noexcept;

  [[nodiscard]]
  const std::vector<Material>& get_materials() const noexcept;

private:
  std::vector<glm::vec3> m_positions;
  std::vector<glm::vec3> m_normals;
  std::vector<glm::vec2> m_tex_coords;
  std::vector<int> m_material_indices;

  std::vector<Material> m_materials;
};

#endif
