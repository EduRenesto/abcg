#ifndef __BACKROOMS_LEVEL_HPP
#define __BACKROOMS_LEVEL_HPP

#include <glm/glm.hpp>

#include "../ecs.hpp"

class Level {
public:
  explicit Level(ECS::World *world) : m_world(world) {};

  void build();

private:
  ECS::World *m_world;

  ECS::Entity *create_cube(glm::vec3 center, glm::vec3 scale);
};

#endif
