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
#include "../asset_manager/asset_manager.hpp"
#include "../asset_manager/mesh_asset.hpp"

class MeshRenderer : public ECS::EntitySystem {
public:
  explicit MeshRenderer(AssetManager& manager, std::shared_ptr<Camera> camera, glm::mat4 proj_matrix) :
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

  std::shared_ptr<Camera> m_camera;
  glm::mat4 m_projection_matrix;

  std::map<std::string, VAOData> m_vaos;
  std::vector<GLuint> m_vbos{};

  std::map<std::string, std::vector<GLuint>> m_textures;
  std::map<std::string, std::vector<GLuint>> m_samplers;

  VAOData get_vao(std::string& asset_name);
  VAOData build_vao(const Mesh& mesh);
  void draw_vao(std::string asset_name, VAOData vao, GLuint shader, Transform& transform);

  std::vector<GLuint>& get_textures(std::string& asset_name);
  std::vector<GLuint> build_textures(const Mesh& mesh);

  std::vector<GLuint>& get_samplers(std::string& asset_name);
  std::vector<GLuint> build_samplers(const Mesh& mesh);
};

#endif
