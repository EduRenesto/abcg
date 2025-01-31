#ifndef __GLBALL_BLOCK_RENDERER_HPP
#define __GLBALL_BLOCK_RENDERER_HPP

#include <GL/glew.h>
#include <array>
#include <glm/glm.hpp>

#include "block.hpp"

namespace glball {
  class BlockRenderer {
  public: 
    BlockRenderer(GLuint shader, float block_width, float block_height);

    void render(const Block& block, glm::mat4 &projection_matrix) const noexcept;

  private:
    GLuint m_block_vbo{};
    GLuint m_block_vao{};

    GLuint m_block_shader{};

    glm::mat3 m_block_scale{};

    constexpr static const std::array<glm::vec2, 6> m_block_vertices = {
      glm::vec2(1.0, 1.0),
      glm::vec2(-1.0, 1.0),
      glm::vec2(-1.0, -1.0),
      glm::vec2(-1.0, -1.0),
      glm::vec2(1.0, -1.0),
      glm::vec2(1.0, 1.0),
    };
  };
}

#endif
