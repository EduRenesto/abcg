#ifndef __DXBALL_PADDLE_RENDERER_HPP
#define __DXBALL_PADDLE_RENDERER_HPP

#include <array>

#include <GL/glew.h>

#include "paddle.hpp"

namespace dxball {
  class PaddleRenderer {
  public:
    PaddleRenderer(GLuint shader, float width, float height);

    void render(Paddle& paddle) const;

  private:
    GLuint m_paddle_vbo{};
    GLuint m_paddle_vao{};

    GLuint m_paddle_shader{};

    glm::mat3 m_block_scale{};

    constexpr static const std::array<glm::vec2, 6> m_paddle_vertices = {
      glm::vec2(1.0, 0.1),
      glm::vec2(-1.0, 0.1),
      glm::vec2(-1.0, -0.1),
      glm::vec2(-1.0, -0.1),
      glm::vec2(1.0, -0.1),
      glm::vec2(1.0, 0.1),
    };
  };
}

#endif
