#include <glm/ext/matrix_clip_space.hpp>

#include "abcg_image.hpp"
#include "components/camera_controller_component.hpp"
#include "gl_window.hpp"

#include "asset_manager/mesh_asset.hpp"
#include "asset_manager/shader_asset.hpp"
#include "asset_manager/texture_asset.hpp"

#include "components/mesh_component.hpp"
#include "components/material_component.hpp"
#include "components/transform_component.hpp"
#include "level/level.hpp"
#include "systems/camera_system.hpp"

GLWindow::GLWindow() {
  this->m_world = ECS::World::createWorld();
  this->m_camera = std::make_shared<Camera>(Camera{});

  const auto window_settings = this->getWindowSettings();
  this->resizeGL(window_settings.width, window_settings.height);

  this->m_asset_manager = AssetManager{};
}

void GLWindow::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glClearColor(0.53, 0.81, 0.92, 1.0);

  const auto assets_path = this->getAssetsPath();

  // Mesh assets
  this->m_asset_manager.add("cube", MeshAsset::build(assets_path + "models/cube.obj"));
  this->m_asset_manager.add("suzanne", MeshAsset::build(assets_path + "models/suzanne.obj"));
  this->m_asset_manager.add("sponza", MeshAsset::build(assets_path + "models/sponza.obj"));

  // Shaders
  this->m_asset_manager.add("unlit", ShaderAsset::build(this->createProgramFromFile(
    assets_path + "shaders/unlit.vs.glsl",
    assets_path + "shaders/unlit.fs.glsl"
  )));

  // Textures
  std::vector<std::pair<std::string, std::string>> textures{
    { "textures/lion.tga", "textures/lion.png" },
    { "textures/background.tga", "textures/background.png" },
    { "textures/vase_plant.tga", "textures/vase_plant.png" },
    { "textures/sponza_arch_diff.tga", "textures/sponza_arch_diff.png" },
    { "textures/spnza_bricks_a_diff.tga", "textures/spnza_bricks_a_diff.png" },
    { "textures/sponza_ceiling_a_diff.tga", "textures/sponza_ceiling_a_diff.png" },
    { "textures/chain_texture.tga", "textures/chain_texture.png" },
    { "textures/sponza_column_a_diff.tga", "textures/sponza_column_a_diff.png" },
    { "textures/sponza_column_b_diff.tga", "textures/sponza_column_b_diff.png" },
    { "textures/sponza_column_c_diff.tga", "textures/sponza_column_c_diff.png" },
    { "textures/sponza_details_diff.tga", "textures/sponza_details_diff.png" },
    { "textures/sponza_fabric_diff.tga", "textures/sponza_fabric_diff.png" },
    { "textures/sponza_curtain_diff.tga", "textures/sponza_curtain_diff.png" },
    { "textures/sponza_fabric_blue_diff.tga", "textures/sponza_fabric_blue_diff.png" },
    { "textures/sponza_fabric_green_diff.tga", "textures/sponza_fabric_green_diff.png" },
    { "textures/sponza_curtain_green_diff.tga", "textures/sponza_curtain_green_diff.png" },
    { "textures/sponza_curtain_blue_diff.tga", "textures/sponza_curtain_blue_diff.png" },
    { "textures/sponza_flagpole_diff.tga", "textures/sponza_flagpole_diff.png" },
    { "textures/sponza_floor_a_diff.tga", "textures/sponza_floor_a_diff.png" },
    { "textures/sponza_thorn_diff.tga", "textures/sponza_thorn_diff.png" },
    { "textures/sponza_roof_diff.tga", "textures/sponza_roof_diff.png" },
    { "textures/vase_dif.tga", "textures/vase_dif.png" },
    { "textures/vase_hanging.tga", "textures/vase_hanging.png" },
    { "textures/vase_round.tga", "textures/vase_round.png" },
    { "textures/default", "textures/default.png" },
  };

  for (auto& pair : textures) {
    auto texture{abcg::opengl::loadTexture(assets_path + pair.second)};

    this->m_asset_manager.add(pair.first, TextureAsset::build(texture));
  }

  // Mesh Renderer system
  this->m_mesh_renderer = std::make_shared<MeshRenderer>(MeshRenderer{
    this->m_asset_manager,
    this->m_camera,
    this->m_proj_matrix
  });
  this->m_world->registerSystem(this->m_mesh_renderer.get());

  // Camera controller system
  this->m_cam_ctrl = std::make_shared<CameraSystem>(CameraSystem{
      this->m_input,
      15.0f,
      0.5f,
  });
  this->m_world->registerSystem(this->m_cam_ctrl.get());

  // Camera controller entity
  auto *camera_control{this->m_world->create()};
  camera_control->assign<CameraControllerComponent>(CameraControllerComponent{
    this->m_camera, 
    glm::vec3{100, 100, 100},
    glm::vec3{0, 0, 0},
    glm::vec3{0.0, 1.0, 0.0},
    true,
  });

  // Build the world
  Level level{this->m_world};
  level.build();
};

void GLWindow::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto dt{this->getDeltaTime()};
  this->m_world->tick((float) dt);
}

void GLWindow::terminateGL() {
  this->m_world->destroyWorld();
}

void GLWindow::handleEvent(SDL_Event &evt) {
  this->m_input.update(evt);
}

void GLWindow::resizeGL(int width, int height) {
  const auto aspect = (double) width / (double) height;

  // Rebuild projection matrix
  this->m_proj_matrix = glm::perspective(
    M_PI / 3.0,
    aspect,
    0.01,
    1000.0
  );
}
