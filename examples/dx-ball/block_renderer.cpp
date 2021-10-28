#include "block_renderer.hpp"

#include <abcg_openglwindow.hpp>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/ext.hpp>
#include <iostream>

dxball::BlockRenderer::BlockRenderer(GLuint shader, float width, float height) {
  this->m_block_shader = shader;

  const auto vec = glm::vec2(width, height);
  std::cout << "vtx:" << glm::to_string(vec) << std::endl;
  this->m_block_scale = glm::scale(glm::mat3(1.0), vec);
  std::cout << "mtx:" << glm::to_string(this->m_block_scale) << std::endl;

  glGenBuffers(1, &this->m_block_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_block_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 6, m_block_vertices.data(), GL_STATIC_DRAW);

  glGenVertexArrays(1, &this->m_block_vao);
  glBindVertexArray(this->m_block_vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void dxball::BlockRenderer::render(const Block& block) const noexcept {
  glUseProgram(this->m_block_shader);
  glBindVertexArray(this->m_block_vao);

  const auto scale_location = glGetUniformLocation(this->m_block_shader, "_scale_matrix");
  glUniformMatrix3fv(scale_location, 1, GL_FALSE, &this->m_block_scale[0][0]);

  const auto position_location = glGetUniformLocation(this->m_block_shader, "_block_position");
  glUniform2iv(position_location, 1, &block.position[0]);

  glBindVertexArray(this->m_block_vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}
