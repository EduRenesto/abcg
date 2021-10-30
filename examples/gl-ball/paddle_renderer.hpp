#ifndef __GLBALL_PADDLE_RENDERER_HPP
#define __GLBALL_PADDLE_RENDERER_HPP

#include <array>

#include <GL/glew.h>

#include "paddle.hpp"

namespace glball {
  class PaddleRenderer {
  public:
    explicit PaddleRenderer(GLuint shader);

    void render(Paddle& paddle, glm::mat4 &projection_matrix) const;

  private:
    GLuint m_paddle_vbo{};
    GLuint m_paddle_vao{};

    GLuint m_paddle_shader{};

    glm::mat3 m_block_scale{};

    constexpr static const std::array<glm::vec2, 6> m_paddle_vertices = {
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
