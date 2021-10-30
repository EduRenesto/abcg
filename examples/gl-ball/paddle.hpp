#ifndef __GLBALL_PADDLE_HPP
#define __GLBALL_PADDLE_HPP

#include <glm/glm.hpp>

#include "ball.hpp"

namespace glball {
  class Paddle {
  public:
    Paddle(glm::vec2 initial_pos, float width, float height);

    void move(float amount);

    void intersect(Ball& ball) const;

    [[nodiscard]]
    glm::vec2 get_scale() const noexcept;

    [[nodiscard]]
    glm::vec2 get_world_position() const noexcept;

  private:
    glm::vec2 m_position;

    float m_width;
    float m_height;
  };
}

#endif
