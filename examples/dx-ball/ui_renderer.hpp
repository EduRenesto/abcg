#ifndef __DXBALL_UI_RENDERER_HPP
#define __DXBALL_UI_RENDERER_HPP

#include <imgui.h>

#include "game_state.hpp"

namespace dxball {
  class UIRenderer {
  public:
    UIRenderer(ImFont *font, int width, int height);

    void render(GameState state);

  private:
    float m_width;
    float m_height;

    ImFont *m_font{};
  };
}

#endif
