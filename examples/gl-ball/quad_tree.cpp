#include "quad_tree.hpp"
#include <glm/geometric.hpp>
#include <optional>
#include <algorithm>

glball::QuadTreeLeaf::QuadTreeLeaf(std::vector<std::shared_ptr<Block>> blocks) {
  this->m_blocks = std::move(blocks);
}

void glball::QuadTreeLeaf::intersects(glball::Ball &ball) {
  for (auto& block : this->m_blocks) {
    if (!block->get_is_active()) continue;

    // Now, we check for collisions on each face of the block.
    // We assume that every block has both width and height equal
    // to 1.0. The world position of each block is the position
    // of its center.

    // We need to check each face separately so that we can
    // calculate the normal and reflect the ball accordingly.
    // There might be a cool way to do this using linear algebra,
    // but it's 23:30 after a long work's wednesday and I'm too
    // tired to think about it xD

    const auto block_center = block->get_world_position();

    const auto ball_position = ball.get_position();
    const auto ball_velocity = ball.get_velocity();
    const auto ball_radius = ball.get_radius();

    // Southern face
    if (
	ball_position.x >= block_center.x - 0.5 &&
	ball_position.x <= block_center.x + 0.5 &&
	ball_position.y <= block_center.y - 0.5 &&
	ball_position.y >= block_center.y - 0.5 - ball_radius
    ) {
      const auto normal = glm::vec2(0.0, -1.0);
      const auto new_velocity = glm::reflect(ball_velocity, normal);

      ball.set_velocity(new_velocity);

      block->increment_hit_count();

      continue;
    }

    // Northern face
    if (
	ball_position.x >= block_center.x - 0.5 &&
	ball_position.x <= block_center.x + 0.5 &&
	ball_position.y >= block_center.y + 0.5 &&
	ball_position.y <= block_center.y + 0.5 + ball_radius
    ) {
      const auto normal = glm::vec2(0.0, 1.0);
      const auto new_velocity = glm::reflect(ball_velocity, normal);

      ball.set_velocity(new_velocity);

      block->increment_hit_count();

      continue;
    }

    // Eastern face
    if (
	ball_position.y >= block_center.y - 0.5 &&
	ball_position.y <= block_center.y + 0.5 &&
	ball_position.x >= block_center.x + 0.5 &&
	ball_position.x <= block_center.x + 0.5 + ball_radius
    ) {
      const auto normal = glm::vec2(1.0, 0.0);
      const auto new_velocity = glm::reflect(ball_velocity, normal);

      ball.set_velocity(new_velocity);

      block->increment_hit_count();

      continue;
    }

    // Western face
    if (
	ball_position.y >= block_center.y - 0.5 &&
	ball_position.y <= block_center.y + 0.5 &&
	ball_position.x <= block_center.x - 0.5 &&
	ball_position.x >= block_center.x - 0.5 - ball_radius
    ) {
      const auto normal = glm::vec2(-1.0, 0.0);
      const auto new_velocity = glm::reflect(ball_velocity, normal);

      ball.set_velocity(new_velocity);

      block->increment_hit_count();

      continue;
    }
  }
}

bool glball::QuadTreeLeaf::has_blocks_left() {
  return std::find_if(
    std::begin(this->m_blocks),
    std::end(this->m_blocks),
    [](auto& block) { return block->get_is_active(); }
  ) != std::end(this->m_blocks);
}

void glball::QuadTreeNode::intersects(glball::Ball &ball) {
  // The idea here is that we do the fewest possible intersection
  // tests. Here, we check in which subplane the ball is, and only
  // test for intersections inside that subplane by recursing into it.
  // This allows us a cool logarithmic time intersection test, instead
  // of a linear time comparison if we were to check against every single
  // possible block.

  // The subplanes are defined by the `center` attribute. If (x0, y0) = center,
  // then we have the following subplanes:
  //  - Top left:  (-infty; x0] x [y0; +infty)
  //  - Top right: [x0; +infty) x [y0; +infty)
  //  - Bot left:  (-infty; x0] x (-infty; y0]
  //  - Bot right: [x0; +infty) x (-infty; y0]

  const auto ball_position = ball.get_position();

  // Top left subplane
  if (
    ball_position.x <= this->center.x &&
    ball_position.y >= this->center.y
  ) {
    this->m_top_left->intersects(ball);
    return;
  }

  // Top right subplane
  if (
    ball_position.x >= this->center.x &&
    ball_position.y >= this->center.y
  ) {
    this->m_top_right->intersects(ball);
    return;
  }

  // Bot left subplane
  if (
    ball_position.x <= this->center.x &&
    ball_position.y <= this->center.y
  ) {
    this->m_bot_left->intersects(ball);
    return;
  }

  // Bot right subplane
  if (
    ball_position.x >= this->center.x &&
    ball_position.y <= this->center.y
  ) {
    this->m_bot_right->intersects(ball);
    return;
  }
}

bool glball::QuadTreeNode::has_blocks_left() {
  return
    this->m_top_left->has_blocks_left() ||
    this->m_top_right->has_blocks_left() ||
    this->m_bot_left->has_blocks_left() ||
    this->m_bot_right->has_blocks_left();
}
