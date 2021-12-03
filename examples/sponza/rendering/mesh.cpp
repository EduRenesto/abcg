#include "mesh.hpp"

const std::vector<glm::vec3>& Mesh::get_positions() const noexcept {
  return this->m_positions;
}

const std::vector<glm::vec3>& Mesh::get_normals() const noexcept {
  return this->m_normals;
}

const std::vector<glm::vec2>& Mesh::get_tex_coords() const noexcept {
  return this->m_tex_coords;
}

const std::vector<int>& Mesh::get_material_indices() const noexcept {
  return this->m_material_indices;
}

const std::vector<Material>& Mesh::get_materials() const noexcept {
  return this->m_materials;
}
