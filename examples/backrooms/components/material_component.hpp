#ifndef __BACKROOMS_MATERIAL_COMPONENT_HPP
#define __BACKROOMS_MATERIAL_COMPONENT_HPP

#include <GL/glew.h>

#include "../ecs.hpp"

/*
 * For now, this `MaterialComponent` is just a struct that
 * holds the handle for the OpenGL shader program.
 */
struct MaterialComponent {
  ECS_DECLARE_TYPE

  std::string asset_name;
} __attribute__((aligned(32)));

ECS_DEFINE_TYPE(MaterialComponent)

#endif
