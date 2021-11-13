#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "mesh_renderer.hpp"
#include "../components/transform.hpp"

void MeshRenderer::configure(ECS::World *world) {
  std::cout << "MeshRenderer::configure" << std::endl;
}

void MeshRenderer::unconfigure(ECS::World *world) {
  std::cout << "MeshRenderer::unconfigure" << std::endl;
}

void MeshRenderer::tick(ECS::World *world, float dt) {
  std::cout << "MeshRenderer::tick(" << dt << ")" << std::endl;

  world->each<Transform>([&] (ECS::Entity *e, ECS::ComponentHandle<Transform> transform) -> void {
    std::cout <<
      "Entity " <<
      e->getEntityId() <<
      " has position " <<
      glm::to_string(transform->position) <<
      std::endl;
  });
}
