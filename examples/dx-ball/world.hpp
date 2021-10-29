#ifndef __DXBALL_WORLD_HPP
#define __DXBALL_WORLD_HPP

#include <optional>
#include "block_renderer.hpp"
#include "ball_renderer.hpp"
#include "quad_tree.hpp"

namespace dxball {
  class World {
  public:
    World();

    void render(BlockRenderer &block_renderer, BallRenderer &ball_renderer);

    void update(float delta);

  private:
    std::optional<Ball> m_ball = std::nullopt;

    std::vector<std::shared_ptr<Block>> m_blocks{};
    std::unique_ptr<QuadTree> m_root_node;
  };
}

#endif
