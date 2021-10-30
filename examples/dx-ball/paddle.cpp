#include "paddle.hpp"
#include <iostream>
#include <math.h>
#include <glm/geometric.hpp>
#include <glm/gtx/rotate_vector.hpp>

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
    ball_position.x >= this->m_position.x - this->m_width &&
    ball_position.x <= this->m_position.x + this->m_width &&
    ball_position.y >= this->m_position.y + this->m_height &&
    ball_position.y <= this->m_position.y + this->m_height + ball.get_radius()
  ) {
    // What we want here is to change the normal, depending on the position
    // the ball hit the paddle. We want the normal to be perpendicular
    // to the paddle when the ball hits exactly its center. We also want it
    // to be rotated -pi/2 when the hit happens at the leftmost point of the
    // paddle, and pi/2 when it happens at the rightmost point of the paddle.

    // Let `A` (resp `B`) be the leftmost (resp rightmost) point of the paddle, and
    // let `p` be the point in which the ball hit the paddle. By construction,
    // `p` is between `A` and `B`. Since we can only consider the `x` coordinate,
    // we can write `p` as a linear interpolation between `A` and `B` (in \mathbb{R}^{1}).
    // Let `alpha` be this interpolation coefficient, ranging from 0
    // to 1 inclusive. Then, we can write the following equation:
    //
    // p = alpha * A + (1 - alpha) * B
    //
    // Doing the maths, we can isolate alpha to be:
    //
    // alpha = (p - B) / (A - B)
    // 
    // So, `alpha` will be 0 when the ball hits the leftmost point, and 1 when
    // the ball hits the rightmost point, and 0.5 dead center. We can then plug
    // `alpha` into some trig function that will give us the values we want.
    // In particular, we can hammer the `arcsin` function to do exactly what we
    // want:
    //
    // f(alpha) = arcsin(2 * alpha - 1)
    //
    // This way, f(alpha) will be -pi/2 when the ball hits the left side, and
    // pi/2 when it hits the right side, just like we wanted.
    // From there, we can just plug in into `glm::rotate` and be happy.
    //
    // Cool, huh?

    const auto A = (this->m_position.x - this->m_width);
    const auto B = (this->m_position.x + this->m_width);
    const auto alpha = (ball_position.x - B) / (A - B);

    const auto angle = asinf(2.0f * alpha - 1.0f);

    const auto normal = glm::vec2(0.0, 1.0);
    const auto rotated_normal = glm::rotate(normal, angle);
    const auto new_velocity = glm::reflect(ball.get_velocity(), rotated_normal);

    ball.set_velocity(new_velocity);
  }
}
