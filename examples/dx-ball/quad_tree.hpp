#ifndef __DXBALL_QUAD_TREE_HPP
#define __DXBALL_QUAD_TREE_HPP

#include <memory>
#include <vector>
#include <optional>

#include <glm/glm.hpp>

#include "ball.hpp"
#include "block.hpp"

namespace dxball {
  class QuadTree {
  public:
    virtual void intersects(Ball &ball) = 0;
  };

  class QuadTreeLeaf : public QuadTree {
  public:
    explicit QuadTreeLeaf(std::vector<std::shared_ptr<Block>> blocks);

    void intersects(Ball &ball) override;

  private:
    std::vector<std::shared_ptr<Block>> m_blocks;
  };

  class QuadTreeNode : public QuadTree {
  public:
    QuadTreeNode(QuadTree top_left, QuadTree top_right, QuadTree bot_left, QuadTree bot_right);

    void intersects(Ball &ball) override;

  private:
    glm::vec2 center;

    std::unique_ptr<QuadTree> m_top_left;
    std::unique_ptr<QuadTree> m_top_right;
    std::unique_ptr<QuadTree> m_bot_left;
    std::unique_ptr<QuadTree> m_bot_right;
  };
}

#endif
