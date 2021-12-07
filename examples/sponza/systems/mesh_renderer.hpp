#ifndef __SPONZA_MESH_RENDERER
#define __SPONZA_MESH_RENDERER

#include <memory>
#include <map>
#include <string>
#include <GL/glew.h>

#include "../ecs.hpp"
#include "../rendering/mesh.hpp"
#include "../rendering/camera.hpp"
#include "../rendering/transform.hpp"
#include "../rendering/render_target.hpp"
#include "../rendering/light.hpp"
#include "../asset_manager/asset_manager.hpp"
#include "../asset_manager/mesh_asset.hpp"
#include "../events/resize_window_event.hpp"

class MeshRenderer : public ECS::EntitySystem, public ECS::EventSubscriber<ResizeWindowEvent> {
public:
  explicit MeshRenderer(
    unsigned int width,
    unsigned int height,
    AssetManager& manager,
    std::shared_ptr<Camera> camera,
    glm::mat4 proj_matrix
  ) :
    m_asset_manager(manager),
    m_camera(camera),
    m_projection_matrix(proj_matrix),
    m_gbuffer(RenderTarget{
      width,
      height,
      false,
      {
	{ GL_RGBA32F, GL_RGBA }, // World space positions
	{ GL_RGBA32F, GL_RGBA }, // Normals
	{ GL_RGBA32F, GL_RGBA }, // Diffuse + Shininess
      }
    })
  {};

  void configure(ECS::World *world) override;

  void unconfigure(ECS::World *world) override;

  void tick(ECS::World *world, float dt) override;

private:
  struct VAOData {
    GLuint vao;
    size_t vertex_count;
    GLuint tex_handle;
    float shininess;
  } __attribute__((aligned(16)));

  AssetManager& m_asset_manager;

  std::shared_ptr<Camera> m_camera;
  glm::mat4 m_projection_matrix;

  std::map<std::string, std::vector<VAOData>> m_vaos;
  std::vector<GLuint> m_vbos{};

  GLuint m_quad_vao{};

  std::vector<VAOData> get_vaos(std::string& asset_name);
  std::vector<VAOData> build_vaos(const std::vector<Mesh>& meshes);
  void draw_vaos(std::vector<VAOData>& vaos, GLuint shader, Transform& transform);

  RenderTarget m_gbuffer;
  void resize_gbuffer(unsigned int width, unsigned int height);

  std::vector<std::pair<Light, RenderTarget>> m_lights{}; // TODO initialize this

  /* Render passes */
  void geometry_pass(
    std::string& mesh_asset_name,
    std::string& material_asset_name,
    Transform& transform
  );
  void shadow_pass(
    std::string& mesh_asset_name,
    Transform& transform
  );
  void lightning_pass();

  /* Event handling */
  void receive(class ECS::World *world, const ResizeWindowEvent& event) override;
};

#endif
