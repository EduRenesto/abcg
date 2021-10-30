#ifndef __GLBALL_BALL_HPP
#define __GLBALL_BALL_HPP

#include <glm/glm.hpp>

namespace glball {
  class Ball {
  public: 
    Ball(glm::vec2 initial_position, float radius, glm::vec2 initial_velocity);

    [[nodiscard]]
    glm::vec2 & get_position();

    [[nodiscard]]
    glm::vec2 & get_velocity();

    [[nodiscard]]
    float & get_radius();

    void set_velocity(glm::vec2 velocity);

    void update(float delta);

  private:
    glm::vec2 position;
    float radius;

    glm::vec2 velocity;
  };
}
#endif
