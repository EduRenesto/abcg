#ifndef __BACKROOMS_CAMERA_SYSTEM_HPP
#define __BACKROOMS_CAMERA_SYSTEM_HPP

#include "../ecs.hpp"

class CameraSystem : public ECS::EntitySystem {
public:
  void configure(ECS::World *world) override;
  void unconfigure(ECS::World *world) override;
  void tick(ECS::World *world, float _dt) override;
};

#endif
