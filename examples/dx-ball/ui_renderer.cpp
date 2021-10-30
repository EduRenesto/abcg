#include "ui_renderer.hpp"
#include <imgui.h>

dxball::UIRenderer::UIRenderer(ImFont *font, int width, int height) {
  this->m_font = font;
  this->m_width = (float) width;
  this->m_height = (float) height;
}

void dxball::UIRenderer::render(dxball::GameState state) {
  if (state == GameState::PLAYING) return;

  const auto size{ImVec2(300, 85)};
  const auto position{ImVec2((this->m_width - size.x) / 2.0f,
			     (this->m_height - size.y) / 2.0f)};
  ImGui::SetNextWindowPos(position);
  ImGui::SetNextWindowSize(size);
  ImGuiWindowFlags flags{ImGuiWindowFlags_NoBackground |
			 ImGuiWindowFlags_NoTitleBar |
			 ImGuiWindowFlags_NoInputs};
  ImGui::Begin(" ", nullptr, flags);
  ImGui::PushFont(m_font);
  ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(101, 123, 131, 255));

  if (state == GameState::FAIL) {
    ImGui::Text("Game Over!");
  } else if (state == GameState::SUCCESS) {
    ImGui::Text("*You Won!*");
  }

  ImGui::PopStyleColor();
  ImGui::PopFont();
  ImGui::End();
}
