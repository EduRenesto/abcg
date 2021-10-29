#include "block.hpp"

dxball::Block::Block(const glm::vec2 position, unsigned int max_hits) {
  this->position = position;
  this->max_hits = max_hits;
}

glm::vec2 dxball::Block::Block::get_world_position() const noexcept {
  return this->position;
}

void dxball::Block::increment_hit_count() {
  this->current_hits++;

  if (this->current_hits > this->max_hits) this->is_active = false;
}

bool dxball::Block::get_is_active() const noexcept {
  return this->is_active;
}
