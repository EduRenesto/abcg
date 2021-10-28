#include "block.hpp"

dxball::Block::Block(const glm::vec2 position, unsigned int max_hits) {
  this->position = position;
  this->max_hits = max_hits;
}

glm::vec2 dxball::Block::Block::get_world_position() const noexcept {
  return this->position;
}
