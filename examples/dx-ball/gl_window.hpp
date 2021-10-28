#ifndef __ORBITS_GL_WINDOW_HPP
#define __ORBITS_GL_WINDOW_HPP

#include <optional>
#include "abcg.hpp"
#include "abcg_openglwindow.hpp"

#include "block_renderer.hpp"

namespace dxball {
  class GLWindow : public abcg::OpenGLWindow {
  public:
    GLWindow() = default;

  protected:
    void initializeGL() override;
    void paintGL() override;
    void terminateGL() override;

  private:
    std::optional<BlockRenderer> m_block_renderer = std::nullopt;
  };
}

#endif
