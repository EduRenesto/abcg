#ifndef __BACKROOMS_GL_WINDOW_HPP
#define __BACKROOMS_GL_WINDOW_HPP

#include "abcg_openglwindow.hpp"

#include "ecs.hpp"
#include "rendering/camera.hpp"
#include "asset_manager/asset_manager.hpp"
#include "systems/mesh_renderer.hpp"

class GLWindow : public abcg::OpenGLWindow {
public:
  GLWindow();

protected:
  void initializeGL() override;
  void paintGL() override;

private:
  ECS::World *m_world;
  Camera m_camera;
  glm::mat4 m_proj_matrix;

  AssetManager m_asset_manager;

  std::shared_ptr<MeshRenderer> m_mesh_renderer;
};

#endif
