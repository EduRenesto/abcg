#ifndef __DXBALL_BLOCK_HPP
#define __DXBALL_BLOCK_HPP

#include <glm/glm.hpp>

namespace dxball {
  class Block {
  public:
    Block(glm::vec2 position, unsigned int max_hits);

    [[nodiscard]]
    glm::vec2 get_world_position() const noexcept;

    void increment_hit_count();

    [[nodiscard]]
    bool get_is_active() const noexcept;

  private:
    glm::vec2 position;

    unsigned int max_hits;
    unsigned int current_hits{0};

    bool is_active{true};
  };
}

#endif
