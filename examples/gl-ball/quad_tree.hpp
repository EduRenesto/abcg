#ifndef __GLBALL_QUAD_TREE_HPP
#define __GLBALL_QUAD_TREE_HPP

#include <memory>
#include <vector>
#include <optional>

#include <glm/glm.hpp>

#include "ball.hpp"
#include "block.hpp"

// The structures described in this file were supposed to be used
// to decrease the amount of collision tests ran during runtime.
// As described in some comments in the .cpp file, using this quad tree
// would allow checking for collisions in logarithmic time, instead of
// in linear time.
//
// However, during development I have been using directly the QuadTreeLeaf
// class, which in itself turns out to be just a container that checks linearly
// for the collisions.
// The performance of using it directly isn't as bad as I thought it would be,
// so I don't think there's really a use for the whole tree thingy. And refactoring
// the `World` class constructor to use everything here (+ debugging it) would need
// a time budget which I don't have. (this project is due tomorrow!!! I'm sorry)
//
// I won't delete what I have done because I had spent too much time working on this
// during the first days of development. And, maybe these things will be of use in the
// next class projects.
//
// So, professor, feel free to skip the `QuadTree` and `QuadTreeNode` classes completely
// and only focus on the `QuadTreeLeaf` class.

namespace glball {
  class QuadTree {
  public:
    virtual void intersects(Ball &ball) = 0;

    virtual bool has_blocks_left() = 0;
  };

  class QuadTreeLeaf : public QuadTree {
  public:
    explicit QuadTreeLeaf(std::vector<std::shared_ptr<Block>> blocks);

    void intersects(Ball &ball) override;

     bool has_blocks_left() override;
  private:
    std::vector<std::shared_ptr<Block>> m_blocks;
  };

  class QuadTreeNode : public QuadTree {
  public:
    QuadTreeNode(QuadTree top_left, QuadTree top_right, QuadTree bot_left, QuadTree bot_right);

    void intersects(Ball &ball) override;

     bool has_blocks_left() override;

  private:
    glm::vec2 center;

    std::unique_ptr<QuadTree> m_top_left;
    std::unique_ptr<QuadTree> m_top_right;
    std::unique_ptr<QuadTree> m_bot_left;
    std::unique_ptr<QuadTree> m_bot_right;
  };
}

#endif
