#include <iostream>
#include <memory>

#include <fmt/format.h>

#include "ecs.hpp"
ECS_TYPE_IMPLEMENTATION;

#include "components/transform.hpp"
#include "systems/mesh_renderer.hpp"

#include "asset_manager/asset_manager.hpp"
#include "asset_manager/mesh_asset.hpp"

int main(int argc, char* argv[]) {
  ECS::World *world = ECS::World::createWorld();

  ECS::EntitySystem *mesh_renderer = world->registerSystem(new MeshRenderer());

  ECS::Entity *ent = world->create();
  auto t = ent->assign<Transform>(Transform{});

  world->tick(1.0);
  world->tick(1.0);
  world->tick(1.0);

  ent->remove<Transform>();
  world->cleanup();
  world->destroyWorld();

  AssetManager manager{};

  /*
  auto suzanne_loc = std::string{"./assets/cube.obj"};
  auto suzanne_asset = std::make_shared<MeshAsset>(MeshAsset{suzanne_loc});
  manager.add("suzanne", std::static_pointer_cast<Asset>(suzanne_asset));
  */

  manager.add("suzanne", MeshAsset::build("./assets/cube.obj"));

  //auto asset = manager.get("suzanne");
  //auto suzanne = std::static_pointer_cast<MeshAsset>(asset);
  auto suzanne = manager.get<MeshAsset>("suzanne");

  fmt::print("vertices count: {}\n", suzanne->get().get_positions().size());
  fmt::print("normals count: {}\n", suzanne->get().get_normals().size());

  return 0;
}
