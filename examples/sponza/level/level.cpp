#include "level.hpp"

#include "../asset_manager/mesh_asset.hpp"
#include "../asset_manager/shader_asset.hpp"

#include "../components/mesh_component.hpp"
#include "../components/material_component.hpp"
#include "../components/transform_component.hpp"

void Level::build() {
  /*
  // Build floor
  this->create_cube(glm::vec3{0.0}, glm::vec3{6.0, 0.1, 10.0});

  // Build ceiling
  this->create_cube(glm::vec3{0.0, 2.05, 0.0}, glm::vec3{6.0, 0.1, 10.0});

  // Build right wall
  this->create_cube(glm::vec3{-3.05, 1.0, 0.0}, glm::vec3{1.0, 2.0, 10.0});

  // Build left wall
  this->create_cube(glm::vec3{3.05, 1.0, 0.0}, glm::vec3{1.0, 2.0, 10.0});

  // Build back left wall
  this->create_cube(glm::vec3{2.5, 1.0, 10.0}, glm::vec3{1.0, 2.0, 10.0});
  */

  auto *ent{this->m_world->create()};
  ent->assign<MeshComponent>(MeshComponent{"sponza"});
  ent->assign<MaterialComponent>(MaterialComponent{"gbuffer"});
  ent->assign<TransformComponent>(TransformComponent{Transform{glm::vec3{}, glm::vec3{0.2}}});
}

ECS::Entity *Level::create_cube(glm::vec3 center, glm::vec3 scale) {
  auto *ent{this->m_world->create()};

  ent->assign<MeshComponent>(MeshComponent{"cube"});
  ent->assign<MaterialComponent>(MaterialComponent{"unlit"});
  ent->assign<TransformComponent>(TransformComponent{Transform{center, scale}});

  return ent;
}
