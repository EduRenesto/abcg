#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include <memory>

#include <fmt/format.h>

#include "abcg_application.hpp"
#include "ecs.hpp"
ECS_TYPE_IMPLEMENTATION;

/*
#include "components/mesh_component.hpp"
#include "components/material_component.hpp"
#include "components/transform_component.hpp"
#include "systems/mesh_renderer.hpp"

#include "asset_manager/asset_manager.hpp"
#include "asset_manager/mesh_asset.hpp"
*/

#include "gl_window.hpp"

int main(int argc, char* argv[]) {
  /*
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

  manager.add("suzanne", MeshAsset::build("./assets/cube.obj"));

  auto cube = manager.get<MeshAsset>("cube");

  fmt::print("vertices count: {}\n", cube->get().get_positions().size());
  fmt::print("normals count: {}\n", cube->get().get_normals().size());
  */

  /*
  AssetManager manager{};

  manager.add("cube", MeshAsset::build("./assets/cube.obj"));

  Camera cam{
    glm::vec3{5.0},
    glm::vec3{0.0},
    glm::vec3{0.0, 1.0, 0.0}
  };

  auto proj_matrix = glm::perspective(
    2.0 * M_PI / 3.0,
    16.0 / 9.0,
    0.001,
    10000.0
  );

  Transform transform{};

  ECS::World *world = ECS::World::createWorld();

  ECS::EntitySystem *mesh_renderer = world->registerSystem(
    new MeshRenderer(manager, cam, proj_matrix)
  );

  ECS::Entity *cube = world->create();
  cube->assign<MeshComponent>(MeshComponent{"cube"});
  cube->assign<MaterialComponent>(MaterialComponent{"unlit"});
  cube->assign<TransformComponent>(TransformComponent{transform});

  world->tick(1.0);
  */

  try {
    abcg::Application app(argc, argv);

    auto window{std::make_unique<GLWindow>()};

    window->setWindowSettings({
	.width = 1280,
	.height = 720,
	.showFullscreenButton = false,
	.title = "BACKROOMS",
    });

    window->setOpenGLSettings({
	.profile = abcg::OpenGLProfile::Core,
	.majorVersion = 4,
	.minorVersion = 1,
	.samples = 4
    });

    app.run(std::move(window));
  } catch (const abcg::Exception &e) {
    fmt::print(stderr, "{}", e.what());
    return -1;
  }

  return 0;
}
