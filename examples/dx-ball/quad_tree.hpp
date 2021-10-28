#ifndef __DXBALL_QUAD_TREE_HPP
#define __DXBALL_QUAD_TREE_HPP

#include <memory>
#include <vector>
#include <optional>

#include <glm/glm.hpp>

#include "block.hpp"

namespace dxball {
  // TODO mover a Ball pra outro arquivo. Tá aqui só pra fast development
  class Ball {
  public: 
    glm::vec2 position;
    float radius;
  };

  class QuadTree {
    virtual std::optional<Block&> intersects() = 0;
  };

  class QuadTreeLeaf : public QuadTree {
  public:
    explicit QuadTreeLeaf(std::vector<Block> blocks);

    std::optional<Block&> intersects() override;

  private:
    std::vector<Block> m_blocks;
  };

  class QuadTreeNode : public QuadTree {
  public:
    QuadTreeNode(QuadTree top_left, QuadTree top_right, QuadTree bot_left, QuadTree bot_right);

    std::optional<Block&> intersects() override;

  private:
    std::unique_ptr<QuadTree> m_top_left;
    std::unique_ptr<QuadTree> m_top_right;
    std::unique_ptr<QuadTree> m_bot_left;
    std::unique_ptr<QuadTree> m_bot_right;
  };
}

#endif
