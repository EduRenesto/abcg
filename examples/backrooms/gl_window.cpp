#include <glm/ext/matrix_clip_space.hpp>

#include "gl_window.hpp"

#include "asset_manager/mesh_asset.hpp"
#include "asset_manager/shader_asset.hpp"

#include "components/mesh_component.hpp"
#include "components/material_component.hpp"
#include "components/transform_component.hpp"

GLWindow::GLWindow() {
  this->m_world = ECS::World::createWorld();
  this->m_camera = Camera{
    glm::vec3{5.0},
    glm::vec3{0.0},
    glm::vec3{0.0, 1.0, 0.0}
  };

  const auto window_settings = this->getWindowSettings();
  const auto aspect = (double) window_settings.width / (double) window_settings.height;

  this->m_proj_matrix = glm::perspective(
    M_PI / 3.0,
    aspect,
    0.01,
    1000.0
  );

  this->m_asset_manager = AssetManager{};
}

void GLWindow::initializeGL() {
  // TODO deinit

  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glClearColor(0.2, 0.0, 0.2, 0.0);

  const auto assets_path = this->getAssetsPath();

  // Mesh assets
  this->m_asset_manager.add("cube", MeshAsset::build(assets_path + "models/cube.obj"));
  this->m_asset_manager.add("suzanne", MeshAsset::build(assets_path + "models/suzanne.obj"));

  // Shaders
  this->m_asset_manager.add("unlit", ShaderAsset::build(this->createProgramFromFile(
    assets_path + "shaders/unlit.vs.glsl",
    assets_path + "shaders/unlit.fs.glsl"
  )));

  // Mesh Renderer system
  this->m_mesh_renderer = std::make_shared<MeshRenderer>(MeshRenderer{
    this->m_asset_manager,
    this->m_camera,
    this->m_proj_matrix
  });
  this->m_world->registerSystem(this->m_mesh_renderer.get());

  // Basic entities
  auto *cube{this->m_world->create()};
  cube->assign<MeshComponent>(MeshComponent{"suzanne"});
  cube->assign<MaterialComponent>(MaterialComponent{"unlit"});
  cube->assign<TransformComponent>(TransformComponent{Transform{}});
};

void GLWindow::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto dt{this->getDeltaTime()};
  this->m_world->tick((float) dt);
}
