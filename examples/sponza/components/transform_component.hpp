#ifndef __SPONZA_TRANSFORM_COMPONENT_HPP
#define __SPONZA_TRANSFORM_COMPONENT_HPP

#include "../ecs.hpp"
#include "../rendering/transform.hpp"

/*
 * Just like the other components, this is just a struct
 * that holds a Transform.
 */
struct TransformComponent {
  ECS_DECLARE_TYPE

  Transform transform;
} __attribute__((aligned(16)));

ECS_DEFINE_TYPE(TransformComponent)

#endif
