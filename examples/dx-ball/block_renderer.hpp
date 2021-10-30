#ifndef __DXBALL_BLOCK_RENDERER_HPP
#define __DXBALL_BLOCK_RENDERER_HPP

#include <GL/glew.h>
#include <array>
#include <glm/glm.hpp>

#include "block.hpp"

namespace dxball {
  class BlockRenderer {
  public: 
    BlockRenderer(GLuint shader, float block_width, float block_height);

    void render(const Block& block) const noexcept;

  private:
    GLuint m_block_vbo{};
    GLuint m_block_vao{};

    GLuint m_block_shader{};

    glm::mat3 m_block_scale{};

    constexpr static const std::array<glm::vec2, 6> m_block_vertices = {
      glm::vec2(0.49, 0.49),
      glm::vec2(-0.49, 0.49),
      glm::vec2(-0.49, -0.49),
      glm::vec2(-0.49, -0.49),
      glm::vec2(0.49, -0.49),
      glm::vec2(0.49, 0.49),
    };
  };
}

#endif
