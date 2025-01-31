#include "world.hpp"
#include <glm/geometric.hpp>
#include <memory>
#include <iostream>

glball::World::World(glm::vec2 bottom_left, glm::vec2 top_right) {
  this->m_bottom_left = bottom_left;
  this->m_top_right = top_right;

  for (int u = -4; u <= 4; u++) {
    for (int v = 0; v <= 4; v++) {
      auto position = glm::vec2{(float) u, (float) v};
      auto block = std::make_shared<Block>(position, 3);

      this->m_blocks.push_back(block);
    }
  }

  this->m_root_node = std::make_unique<QuadTreeLeaf>(this->m_blocks);

  auto initial_velocity = glm::vec2{0.0, 1.0};

  this->m_ball = std::optional(Ball{glm::vec2{0.0, -2.0}, 0.1, glm::normalize(initial_velocity)});

  this->m_paddle = std::optional(Paddle{glm::vec2{0.0, -5.0}, 1.0, 0.1});
}

void glball::World::render(
  glm::mat4 &projection_matrix,
  glball::BlockRenderer &renderer,
  glball::BallRenderer &ball_renderer,
  glball::PaddleRenderer &paddle_renderer
) {
  if (this->m_state != GameState::PLAYING) return;

  for (auto& block : this->m_blocks) {
    renderer.render(*block, projection_matrix);
  }

  ball_renderer.render(this->m_ball.value(), projection_matrix);

  paddle_renderer.render(this->m_paddle.value(), projection_matrix);
}

void glball::World::renderUI(glball::UIRenderer &ui_renderer) {
  ui_renderer.render(this->m_state);
}

void glball::World::update(float delta) {
  if (this->m_state != GameState::PLAYING) return;

  this->m_ball.value().update(delta);

  this->m_paddle.value().move(this->m_current_paddle_speed * delta);
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

    return;
  }

  // Eastern wall
  if (ball_position.x > this->m_top_right.x - ball_radius) {
    const auto normal = glm::vec2{-1.0, 0.0};
    const auto new_velocity = glm::reflect(this->m_ball.value().get_velocity(), normal);
    this->m_ball.value().set_velocity(new_velocity);

    return;
  }

  // Northern wall
  if (ball_position.y > this->m_top_right.y - ball_radius) {
    const auto normal = glm::vec2{0.0, -1.0};
    const auto new_velocity = glm::reflect(this->m_ball.value().get_velocity(), normal);
    this->m_ball.value().set_velocity(new_velocity);

    return;
  }

  // Southern wall
  if (ball_position.y < this->m_bottom_left.y + ball_radius) {
    this->m_state = GameState::FAIL;

    return;
  }

  // Check if the user won the game
  if (!this->m_root_node->has_blocks_left()) {
    this->m_state = GameState::SUCCESS;
  }
}

void glball::World::handle_event(InputEvent evt) {
  switch (evt) {
  case InputEvent::NONE:
    this->m_current_paddle_speed = 0.0;
    break;
  case InputEvent::LEFT:
    this->m_current_paddle_speed = -this->m_paddle_speed;
    break;
  case InputEvent::RIGHT:
    this->m_current_paddle_speed = this->m_paddle_speed;
    break;
  }
}
