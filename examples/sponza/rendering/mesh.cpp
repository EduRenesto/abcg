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

const Material& Mesh::get_material() const noexcept {
  return this->m_material;
}
