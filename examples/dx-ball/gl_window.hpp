#ifndef __ORBITS_GL_WINDOW_HPP
#define __ORBITS_GL_WINDOW_HPP

#include <chrono>
#include <optional>

#include "abcg.hpp"
#include "abcg_openglwindow.hpp"
#include "block_renderer.hpp"
#include "ball_renderer.hpp"
#include "world.hpp"

namespace dxball {
  class GLWindow : public abcg::OpenGLWindow {
  public:
    GLWindow();

  protected:
    void initializeGL() override;

    void paintGL() override;
    void terminateGL() override;

  private:
    void render();
    void update(float delta);

    std::chrono::time_point<std::chrono::steady_clock> m_last_frame;

    std::optional<BlockRenderer> m_block_renderer = std::nullopt;
    std::optional<BallRenderer> m_ball_renderer = std::nullopt;
    World m_world;
  };
}

#endif
