#include "world.hpp"
#include <glm/geometric.hpp>
#include <memory>
#include <iostream>

dxball::World::World(glm::vec2 bottom_left, glm::vec2 top_right) {
  this->m_bottom_left = bottom_left;
  this->m_top_right = top_right;

  // TODO make this parametrizable

  for (int u = -3; u <= 3; u++) {
    for (int v = 0; v <= 3; v++) {
      auto position = glm::vec2{(float) u, (float) v};
      auto block = std::make_shared<Block>(position, 3);

      this->m_blocks.push_back(block);
    }
  }

  this->m_root_node = std::make_unique<QuadTreeLeaf>(this->m_blocks);

  auto initial_velocity = glm::vec2{0.5, 1.0};

  this->m_ball = std::optional(Ball{glm::vec2{0.0, -2.0}, 0.1, glm::normalize(initial_velocity)});

  this->m_paddle = std::optional(Paddle{glm::vec2{0.0, -3.0}, 4.0, 0.1});
}

void dxball::World::render(
  glm::mat4 &projection_matrix,
  dxball::BlockRenderer &renderer,
  dxball::BallRenderer &ball_renderer,
  dxball::PaddleRenderer &paddle_renderer
) {
  for (auto& block : this->m_blocks) {
    renderer.render(*block, projection_matrix);
  }

  ball_renderer.render(this->m_ball.value(), projection_matrix);

  paddle_renderer.render(this->m_paddle.value(), projection_matrix);
}

void dxball::World::update(float delta) {
  this->m_ball.value().update(delta);

  this->m_paddle.value().intersect(this->m_ball.value());

  this->m_root_node->intersects(this->m_ball.value());

  // Check whether the ball goes off screen

  const auto ball_position = this->m_ball.value().get_position();
  const auto ball_radius = this->m_ball.value().get_radius();

  // Western wall
  if (ball_position.x < this->m_bottom_left.x + ball_radius) {
    const auto normal = glm::vec2{1.0, 0.0};
    const auto new_velocity = glm::reflect(this->m_ball.value().get_velocity(), normal);
    this->m_ball.value().set_velocity(new_velocity);

    std::cout << "hit western wall" << std::endl;

    return;
  }

  // Eastern wall
  if (ball_position.x > this->m_top_right.x - ball_radius) {
    const auto normal = glm::vec2{-1.0, 0.0};
    const auto new_velocity = glm::reflect(this->m_ball.value().get_velocity(), normal);
    this->m_ball.value().set_velocity(new_velocity);

    std::cout << "hit eastern wall" << std::endl;

    return;
  }

  // Northern wall
  if (ball_position.y > this->m_top_right.y - ball_radius) {
    const auto normal = glm::vec2{0.0, -1.0};
    const auto new_velocity = glm::reflect(this->m_ball.value().get_velocity(), normal);
    this->m_ball.value().set_velocity(new_velocity);

    std::cout << "hit northern wall" << std::endl;

    return;
  }

  // Southern wall
  if (ball_position.y < this->m_bottom_left.y + ball_radius) {
    // TODO game over!
    const auto normal = glm::vec2{0.0, 1.0};
    const auto new_velocity = glm::reflect(this->m_ball.value().get_velocity(), normal);
    this->m_ball.value().set_velocity(new_velocity);

    std::cout << "hit southern wall" << std::endl;

    return;
  }
}
