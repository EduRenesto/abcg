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

    glm::vec2 velocity;
  };

  class QuadTree {
  public:
    virtual void intersects(Ball &ball) = 0;
  };

  class QuadTreeLeaf : public QuadTree {
  public:
    explicit QuadTreeLeaf(std::vector<Block> blocks);

    void intersects(Ball &ball) override;

  private:
    std::vector<Block> m_blocks;
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
