#ifndef __SPONZA_MESH_HPP
#define __SPONZA_MESH_HPP

#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
  Mesh(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals) :
    m_positions(std::move(positions)),
    m_normals(std::move(normals))
  {}

  [[nodiscard]]
  const std::vector<glm::vec3>& get_positions() const noexcept;

  [[nodiscard]]
  const std::vector<glm::vec3>& get_normals() const noexcept;

private:
  std::vector<glm::vec3> m_positions;
  std::vector<glm::vec3> m_normals;
  // SPOILER: std::vector<glm::vec2> m_tex_coords;
};

#endif
