#ifndef __BACKROOMS_MESH_RENDERER
#define __BACKROOMS_MESH_RENDERER

#include "../ecs.hpp"

class MeshRenderer : public ECS::EntitySystem {
  void configure(ECS::World *world) override;

  void unconfigure(ECS::World *world) override;

  void tick(ECS::World *world, float dt) override;
};

#endif
