#include "mesh.hpp"

const std::vector<glm::vec3>& Mesh::get_positions() const noexcept {
  return this->m_positions;
}

const std::vector<glm::vec3>& Mesh::get_normals() const noexcept {
  return this->m_normals;
}
