#include "paddle.hpp"
#include <glm/geometric.hpp>

dxball::Paddle::Paddle(glm::vec2 initial_pos, float width, float height) {
  this->m_position = initial_pos;
  this->m_width = width;
  this->m_height = height;
}

void dxball::Paddle::move(float amount) {
  this->m_position += glm::vec2{amount, 0.0};
}

glm::vec2 dxball::Paddle::get_scale() const noexcept {
  return glm::vec2{this->m_width, this->m_height};
}

glm::vec2 dxball::Paddle::get_world_position() const noexcept {
  return this->m_position;
}

void dxball::Paddle::intersect(Ball &ball) const {
  const auto ball_position = ball.get_position();

  if (
    ball_position.x >= this->m_position.x - this->m_width / 2.0 &&
    ball_position.x <= this->m_position.x + this->m_width / 2.0 &&
    ball_position.y >= this->m_position.y + this->m_height / 2.0 &&
    ball_position.y <= this->m_position.y + this->m_height / 2.0 + ball.get_radius()
  ) {
    const auto normal = glm::vec2(0.0, 1.0);
    const auto new_velocity = glm::reflect(ball.get_velocity(), normal);

    ball.set_velocity(new_velocity);
  }
}
