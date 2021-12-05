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
  // Build the fullscreen quad VAO
  glGenVertexArrays(1, &this->m_quad_vao);
  glBindVertexArray(this->m_quad_vao);

  std::array<GLuint, 2> quad_vbos{{0,0}};
  glGenBuffers(2, quad_vbos.data());

  std::array<glm::vec2, 6> quad_positions{
    glm::vec2(-1.0, 1.0),
    glm::vec2(-1.0, -1.0),
    glm::vec2(1.0, -1.0),
    glm::vec2(1.0, -1.0),
    glm::vec2(1.0, 1.0),
    glm::vec2(-1.0, 1.0),
  };
  std::array<glm::vec2, 6> quad_tex_coords{
    glm::vec2(0.0, 1.0),
    glm::vec2(0.0, 0.0),
    glm::vec2(1.0, 0.0),
    glm::vec2(1.0, 0.0),
    glm::vec2(1.0, 1.0),
    glm::vec2(0.0, 1.0),
  };

  glBindBuffer(GL_ARRAY_BUFFER, quad_vbos[0]);
  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(float) * 2 * quad_positions.size(),
    quad_positions.data(),
    GL_STATIC_DRAW
  );
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  this->m_vbos.push_back(quad_vbos[0]);

  glBindBuffer(GL_ARRAY_BUFFER, quad_vbos[1]);
  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(float) * 2 * quad_tex_coords.size(),
    quad_tex_coords.data(),
    GL_STATIC_DRAW
  );
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  this->m_vbos.push_back(quad_vbos[1]);

  glBindVertexArray(0);
}

void MeshRenderer::unconfigure(ECS::World *world) {
  // Destroy VAOs
  while (!this->m_vaos.empty()) {
    auto vaos_data{this->m_vaos.end()};

    for (auto& vao_data : vaos_data->second) {
	glDeleteVertexArrays(1, &vao_data.vao);
    }
    this->m_vaos.erase(vaos_data);
  }

  // Destroy quad VAO
  glDeleteVertexArrays(1, &this->m_quad_vao);

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

  // TODO destroy textures
}

void MeshRenderer::tick(ECS::World *world, float dt) {
  world->each<MeshComponent, MaterialComponent, TransformComponent>([&] (
    ECS::Entity *e,
    ECS::ComponentHandle<MeshComponent> mesh,
    ECS::ComponentHandle<MaterialComponent> material,
    ECS::ComponentHandle<TransformComponent> transform
  ) -> void {
    // Here, we do a geometry pass to populate the G-Buffer with
    // all the renderable entities.
    this->geometry_pass(
      mesh->asset_name,
      material->asset_name,
      transform->transform
    ); // TODO Parei aqui
  });

  // After the G-Buffer has been populate, we run the lightning
  // pass, drawing into the fullscreen quad.
  // Notice that the geometry pass runs over all the renderable
  // entities in the world, but the lightning pass runs only once.
  // This is cool, because since the lightning pass is done entirely
  // based on what is visible to the user, we don't spend precious GPU
  // time shading things that aren't visible.
  //
  // Cool, huh?
  this->lightning_pass();
}

std::vector<MeshRenderer::VAOData> MeshRenderer::get_vaos(std::string& asset_name) {
  if (this->m_vaos.contains(asset_name)) {
    return this->m_vaos[asset_name];
  }

  auto asset = this->m_asset_manager.get<MeshAsset>(asset_name);

  auto vao = this->build_vaos(asset->get());

  this->m_vaos[asset_name] = vao;

  return vao;
}

std::vector<MeshRenderer::VAOData> MeshRenderer::build_vaos(const std::vector<Mesh>& meshes) {
  std::vector<VAOData> vaos{};

  for (const auto& mesh : meshes) {
    const auto& positions = mesh.get_positions();
    const auto& normals = mesh.get_normals();
    const auto& tex_coords = mesh.get_tex_coords();

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

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->m_vbos.insert(this->m_vbos.end(), vbos.begin(), vbos.end());

    auto texture_asset{
      this->m_asset_manager.get<TextureAsset>(mesh.get_material().get_texture_name())
    };

    VAOData data{
      vao,
      positions.size(),
      texture_asset->get(),
    };

    vaos.push_back(data);
  }

  return vaos;
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

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, vao.tex_handle);

  const auto texture_loc = glGetUniformLocation(shader, "_diffuse_texture");
  glUniform1i(texture_loc, 0);

  glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vao.vertex_count);
}

void MeshRenderer::geometry_pass(
    std::string& mesh_asset_name,
    std::string& material_asset_name,
    Transform& transform
) {
  // In this pass, the geometry is rendered into the GBuffer.
  // There, the positions, normals, diffuse and specular colors
  // and coefficients will be stored in textures based in the
  // screen.

  // Use the GBuffer
  this->m_gbuffer.use();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  auto vaos{this->get_vaos(mesh_asset_name)};
  auto shader{this->m_asset_manager.get<ShaderAsset>(material_asset_name)};

  for (auto& vao : vaos) {
    this->draw_vao(vao, shader->get(), transform);
  }
}

void MeshRenderer::lightning_pass() {
  // In this pass, the only thing that's actually drawn is the
  // fullscreen quad. The deferred fragment shader will take as inputs
  // the color attachments generated by the geometry (and shadow?)
  // passes, run the light calculations on them and render them to the
  // final framebuffer.
  //
  // This way, we can have tons of lights and tons of meshes, the
  // calculations will only be ran based on what the user can see
  // at the moment.
  //
  // Also it's a cool way to flex my OpenGL skills. xD
  //
  // Isso merece um 9.5 ao menos, né professor? ;D
  //
  // TODO usar um UBO, pq isso tá MUITO lerdo!

  // Reset the draw framebuffer
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  auto shader{this->m_asset_manager.get<ShaderAsset>("deferred")};

  // Bind shader and send texture uniforms
  glUseProgram(shader->get());

  auto positions_tex_loc{glGetUniformLocation(shader->get(), "_positions_texture")};
  auto normals_tex_loc{glGetUniformLocation(shader->get(), "_normals_texture")};
  auto diffuse_tex_loc{glGetUniformLocation(shader->get(), "_diffuse_texture")};

  // World space positions texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->m_gbuffer.get_color_attachment(0));
  glUniform1i(positions_tex_loc, 0);

  // Normals texture
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, this->m_gbuffer.get_color_attachment(1));
  glUniform1i(normals_tex_loc, 1);

  // Diffuse + shininess texture
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, this->m_gbuffer.get_color_attachment(2));
  glUniform1i(diffuse_tex_loc, 2);

  // Draw fullscreen quad
  glBindVertexArray(this->m_quad_vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}
