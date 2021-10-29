#ifndef __DXBALL_BALL_RENDERER_HPP
#define __DXBALL_BALL_RENDERER_HPP

#include <GL/glew.h>
#include <array>

#include "ball.hpp"

namespace dxball {
  class BallRenderer {
  public:
    BallRenderer(GLuint shader, float width, float height);

    void render(Ball& ball) const noexcept;

  private:
    GLuint m_ball_vbo{};
    GLuint m_ball_vao{};

    GLuint m_ball_shader{};

    glm::mat3 m_block_scale{};

    constexpr static const std::array<glm::vec2, 1> m_ball_vertices = {
      glm::vec2(0.0, 0.0),
    };
  };
}

#endif
