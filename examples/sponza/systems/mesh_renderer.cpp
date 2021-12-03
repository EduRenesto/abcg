#include <iostream>
#include <array>

#include <glm/gtx/string_cast.hpp>
#include <fmt/format.h>

#include "mesh_renderer.hpp"

#include "../components/mesh_component.hpp"
#include "../components/material_component.hpp"
#include "../components/transform_component.hpp"

#include "../asset_manager/shader_asset.hpp"
#include "../asset_manager/texture_asset.hpp"

void MeshRenderer::configure(ECS::World *_world) {
  /* do nothing */
}

void MeshRenderer::unconfigure(ECS::World *world) {
  // Destroy VAOs
  while (!this->m_vaos.empty()) {
    auto data{this->m_vaos.end()};
    glDeleteVertexArrays(1, &data->second.vao);
    this->m_vaos.erase(data);
  }

  // Destroy VBOs
  glDeleteBuffers(this->m_vbos.size(), this->m_vbos.data());
  this->m_vbos.clear();

  // Destroy shaders
  world->each<MaterialComponent>([&] (
    ECS::Entity *e,
    ECS::ComponentHandle<MaterialComponent> material
  ) -> void {
    auto shader{this->m_asset_manager.get<ShaderAsset>(material->asset_name)};
    glDeleteProgram(shader->get());
  });
}

void MeshRenderer::tick(ECS::World *world, float dt) {
  world->each<MeshComponent, MaterialComponent, TransformComponent>([&] (
    ECS::Entity *e,
    ECS::ComponentHandle<MeshComponent> mesh,
    ECS::ComponentHandle<MaterialComponent> material,
    ECS::ComponentHandle<TransformComponent> transform
  ) -> void {
    auto vao{this->get_vao(mesh->asset_name)};
    auto shader{this->m_asset_manager.get<ShaderAsset>(material->asset_name)};

    this->draw_vao(mesh->asset_name, vao, shader->get(), transform->transform);
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
  const auto& tex_coords = mesh.get_tex_coords();
  const auto& material_indices = mesh.get_material_indices();

  GLuint vao{};
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  std::array<GLuint, 4> vbos{{0,0,0,0}};
  //GLuint vbos[2];
  glGenBuffers(4, &vbos[0]);

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

  // Tex coords buffer
  glBindBuffer(GL_ARRAY_BUFFER, vbos[2]);
  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(float) * 2 * tex_coords.size(),
    tex_coords.data(),
    GL_STATIC_DRAW
  );
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

  // Material indices buffer
  glBindBuffer(GL_ARRAY_BUFFER, vbos[3]);
  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(int) * 1 * material_indices.size(),
    material_indices.data(),
    GL_STATIC_DRAW
  );
  glEnableVertexAttribArray(3);
  glVertexAttribIPointer(3, 1, GL_INT, 0, nullptr);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  this->m_vbos.insert(this->m_vbos.end(), vbos.begin(), vbos.end());

  VAOData data{vao, positions.size()};

  return data;
}

void MeshRenderer::draw_vao(std::string asset_name, VAOData vao, GLuint shader, Transform& transform) {
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

  auto& textures{this->get_textures(asset_name)};
  auto& samplers{this->get_samplers(asset_name)};
  auto n_texs{textures.size()};

  for (unsigned int i = 0; i < n_texs; i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, textures[i]);
  }

  const auto textures_loc = glGetUniformLocation(shader, "_textures");
  glUniform1uiv(textures_loc, n_texs, samplers.data());

  glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vao.vertex_count);
}

std::vector<GLuint>& MeshRenderer::get_textures(std::string& asset_name) {
  if (this->m_textures.contains(asset_name)) {
    return this->m_textures[asset_name];
  }

  auto asset = this->m_asset_manager.get<MeshAsset>(asset_name);

  auto textures = this->build_textures(asset->get());

  this->m_textures[asset_name] = textures;

  return this->m_textures[asset_name];
}

std::vector<GLuint> MeshRenderer::build_textures(const Mesh& mesh) {
  std::vector<GLuint> textures{};

  for(const auto& material : mesh.get_materials()) {
    auto tex{this->m_asset_manager.get<TextureAsset>(material.get_texture_name())};

    textures.push_back(tex->get());
  }

  return textures;
}

std::vector<GLuint>& MeshRenderer::get_samplers(std::string& asset_name) {
  if (this->m_samplers.contains(asset_name)) {
    return this->m_samplers[asset_name];
  }

  auto asset = this->m_asset_manager.get<MeshAsset>(asset_name);

  auto textures = this->build_samplers(asset->get());

  this->m_samplers[asset_name] = textures;

  return this->m_samplers[asset_name];
}

std::vector<GLuint> MeshRenderer::build_samplers(const Mesh& mesh) {
  std::vector<GLuint> samplers{};

  //for(const auto& material : mesh.get_materials()) {
  for(unsigned int i = 0; i < mesh.get_materials().size(); i++) {
    samplers.push_back(i);
  }

  return samplers;
}
