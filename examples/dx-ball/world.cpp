#include "world.hpp"
#include <glm/geometric.hpp>
#include <memory>

dxball::World::World() {
  // TODO make this parametrizable

  for (int u = -3; u <= 3; u++) {
    for (int v = 0; v <= 3; v++) {
      auto position = glm::vec2{(float) u, (float) v};
      auto block = std::make_shared<Block>(position, 3);

      this->m_blocks.push_back(block);
    }
  }

  this->m_root_node = std::make_unique<QuadTreeLeaf>(this->m_blocks);

  auto initial_velocity = glm::vec2{0.0, 1.0};

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
}
