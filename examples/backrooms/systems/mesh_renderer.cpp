#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <fmt/format.h>

#include "mesh_renderer.hpp"

#include "../components/mesh_component.hpp"
#include "../components/material_component.hpp"
#include "../components/transform_component.hpp"

#include "../asset_manager/shader_asset.hpp"

void MeshRenderer::configure(ECS::World *world) {
  std::cout << "MeshRenderer::configure" << std::endl;
}

void MeshRenderer::unconfigure(ECS::World *world) {
  // TODO destroy VAOs
  std::cout << "MeshRenderer::unconfigure" << std::endl;
}

void MeshRenderer::tick(ECS::World *world, float dt) {
  world->each<MeshComponent, MaterialComponent, TransformComponent>([&] (
    ECS::Entity *e,
    ECS::ComponentHandle<MeshComponent> mesh,
    ECS::ComponentHandle<MaterialComponent> material,
    ECS::ComponentHandle<TransformComponent> transform
  ) -> void {
    /*
    fmt::print(
      "[MeshRenderer] Should render entity {} with mesh {}, material {}\n",
      e->getEntityId(),
      mesh->asset_name,
      material->asset_name
    );
    */

    auto vao{this->get_vao(mesh->asset_name)};
    auto shader{this->m_asset_manager.get<ShaderAsset>(material->asset_name)};

    this->draw_vao(vao, shader->get(), transform->transform);
  });
}

MeshRenderer::VAOData MeshRenderer::get_vao(std::string& asset_name) {
  if (this->m_vaos.contains(asset_name)) {
    return this->m_vaos[asset_name];
  }

  auto asset = this->m_asset_manager.get<MeshAsset>(asset_name);

  auto vao = this->build_vao(asset->get());

  this->m_vaos[asset_name] = vao;

  return vao;
}

MeshRenderer::VAOData MeshRenderer::build_vao(const Mesh& mesh) {
  const auto& positions = mesh.get_positions();
  const auto& normals = mesh.get_normals();

  GLuint vao{};
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  //std::array<GLuint, 2> vbos{0,0};
  GLuint vbos[2];
  glGenBuffers(2, &vbos[0]);

  // Positions buffer
  glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(float) * 3 * positions.size(),
    positions.data(),
    GL_STATIC_DRAW
  );
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  // Normals buffer
  glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(float) * 3 * normals.size(),
    normals.data(),
    GL_STATIC_DRAW
  );
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  VAOData data{vao, positions.size()};

  return data;
}

void MeshRenderer::draw_vao(VAOData vao, GLuint shader, Transform& transform) {
  const auto& model_mtx = transform.build_model_matrix();
  const auto& view_mtx = this->m_camera->build_view_matrix();

  glUseProgram(shader);
  glBindVertexArray(vao.vao);

  const auto model_loc = glGetUniformLocation(shader, "_model_matrix");
  const auto view_loc = glGetUniformLocation(shader, "_view_matrix");
  const auto proj_loc = glGetUniformLocation(shader, "_projection_matrix");

  glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model_mtx[0][0]);
  glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view_mtx[0][0]);
  glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &this->m_projection_matrix[0][0]);

  glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vao.vertex_count);
}
