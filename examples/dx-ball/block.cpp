#include "block.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

dxball::Block::Block(const glm::vec2 position, unsigned int max_hits) {
  this->m_position = position;
  this->m_max_hits = max_hits;
}

glm::vec2 dxball::Block::Block::get_world_position() const noexcept {
  return this->m_position;
}

void dxball::Block::increment_hit_count() {
  this->m_current_hits++;

  if (this->m_current_hits > this->m_max_hits) this->m_is_active = false;
}

bool dxball::Block::get_is_active() const noexcept {
  return this->m_is_active;
}

float dxball::Block::get_current_life() const noexcept {
  return ((float) this->m_current_hits) / ((float) this->m_max_hits);
}
