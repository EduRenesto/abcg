#ifndef __ORBITS_GL_WINDOW_HPP
#define __ORBITS_GL_WINDOW_HPP

#include <chrono>
#include <optional>

#include "SDL_events.h"
#include "abcg.hpp"
#include "abcg_openglwindow.hpp"
#include "block_renderer.hpp"
#include "ball_renderer.hpp"
#include "imgui.h"
#include "paddle_renderer.hpp"
#include "world.hpp"
#include "ui_renderer.hpp"

namespace dxball {
  class GLWindow : public abcg::OpenGLWindow {
  public:
    GLWindow();

  protected:
    void initializeGL() override;
    void terminateGL() override;

    void paintGL() override;
    void paintUI() override;

    void handleEvent(SDL_Event &event) override;

  private:
    void render();
    void update(float delta);

    std::chrono::time_point<std::chrono::steady_clock> m_last_frame;

    glm::mat4 m_projection_matrix;

    std::optional<UIRenderer> m_ui_renderer = std::nullopt;
    std::optional<BlockRenderer> m_block_renderer = std::nullopt;
    std::optional<BallRenderer> m_ball_renderer = std::nullopt;
    std::optional<PaddleRenderer> m_paddle_renderer = std::nullopt;

    std::optional<World> m_world = std::nullopt;
  };
}

#endif
