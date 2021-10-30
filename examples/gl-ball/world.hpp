#ifndef __GLBALL_WORLD_HPP
#define __GLBALL_WORLD_HPP

#include <optional>

#include "game_state.hpp"
#include "ui_renderer.hpp"
#include "block_renderer.hpp"
#include "ball_renderer.hpp"
#include "paddle_renderer.hpp"
#include "quad_tree.hpp"

namespace glball {
  enum InputEvent {
    NONE,
    LEFT,
    RIGHT,
  };

  class World {
  public:
    World(glm::vec2 bottom_left, glm::vec2 top_right);

    void render(
      glm::mat4 &projection_matrix,
      BlockRenderer &block_renderer,
      BallRenderer &ball_renderer,
      PaddleRenderer &paddle_renderer
    );

    void renderUI(
      UIRenderer &ui_renderer
    );

    void update(float delta);

    void handle_event(InputEvent evt);

  private:
    GameState m_state{GameState::PLAYING};

    glm::vec2 m_bottom_left;
    glm::vec2 m_top_right;

    std::optional<Ball> m_ball = std::nullopt;

    std::optional<Paddle> m_paddle = std::nullopt;

    float m_paddle_speed{5.0};
    float m_current_paddle_speed{0.0};

    std::vector<std::shared_ptr<Block>> m_blocks{};
    std::unique_ptr<QuadTree> m_root_node;
  };
}

#endif
