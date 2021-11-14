#ifndef __BACKROOMS_MESH_RENDERER
#define __BACKROOMS_MESH_RENDERER

#include <map>
#include <string>
#include <GL/glew.h>

#include "../ecs.hpp"
#include "../rendering/mesh.hpp"
#include "../rendering/camera.hpp"
#include "../rendering/transform.hpp"
#include "../asset_manager/asset_manager.hpp"
#include "../asset_manager/mesh_asset.hpp"

class MeshRenderer : public ECS::EntitySystem {
public:
  explicit MeshRenderer(AssetManager& manager, const Camera& camera, glm::mat4 proj_matrix) :
    m_asset_manager(manager),
    m_camera(camera),
    m_projection_matrix(proj_matrix)
  {};

  void configure(ECS::World *world) override;

  void unconfigure(ECS::World *world) override;

  void tick(ECS::World *world, float dt) override;

private:
  struct VAOData {
    GLuint vao;
    size_t vertex_count;
  } __attribute__((aligned(16)));

  AssetManager& m_asset_manager;

  const Camera& m_camera;

  glm::mat4 m_projection_matrix;

  std::map<std::string, VAOData> m_vaos;

  VAOData get_vao(std::string& asset_name);

  VAOData build_vao(const Mesh& mesh);

  void draw_vao(VAOData vao, GLuint shader, Transform& transform);
};

#endif
