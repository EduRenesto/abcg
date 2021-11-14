#ifndef __BACKROOMS_MESH_COMPONENT_HPP
#define __BACKROOMS_MESH_COMPONENT_HPP

#include <string>

#include "../ecs.hpp"

/*
 * The `MeshComponent` is just a struct that holds a string. The
 * string is used as an asset identifier.
 */
struct MeshComponent {
  ECS_DECLARE_TYPE

  std::string asset_name;
} __attribute__((aligned(32)));

ECS_DEFINE_TYPE(MeshComponent)

#endif
