#ifndef __SPONZA_CAMERA_SYSTEM_HPP
#define __SPONZA_CAMERA_SYSTEM_HPP

#include "../ecs.hpp"
#include "../input.hpp"

class CameraSystem : public ECS::EntitySystem {
public:
  explicit CameraSystem(const Input &input, float speed, float rotation_speed) :
    m_input(input),
    m_translation_speed(speed),
    m_rotation_speed(rotation_speed)
  {};

  void configure(ECS::World *world) override;
  void unconfigure(ECS::World *world) override;
  void tick(ECS::World *world, float _dt) override;

private:
  const Input &m_input;

  float m_translation_speed;
  float m_rotation_speed;

  bool m_print_info{true};
};

#endif
