#ifndef __DXBALL_WORLD_HPP
#define __DXBALL_WORLD_HPP

#include <optional>

#include "block_renderer.hpp"
#include "ball_renderer.hpp"
#include "paddle_renderer.hpp"
#include "quad_tree.hpp"

namespace dxball {
  class World {
  public:
    World(glm::vec2 bottom_left, glm::vec2 top_right);

    void render(
      glm::mat4 &projection_matrix,
      BlockRenderer &block_renderer,
      BallRenderer &ball_renderer,
      PaddleRenderer &paddle_renderer
    );

    void update(float delta);

  private:
    glm::vec2 m_bottom_left;
    glm::vec2 m_top_right;

    std::optional<Ball> m_ball = std::nullopt;

    std::optional<Paddle> m_paddle = std::nullopt;

    std::vector<std::shared_ptr<Block>> m_blocks{};
    std::unique_ptr<QuadTree> m_root_node;
  };
}

#endif
