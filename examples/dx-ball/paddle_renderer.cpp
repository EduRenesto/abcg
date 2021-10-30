#include "paddle_renderer.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

dxball::PaddleRenderer::PaddleRenderer(GLuint shader, float width, float height) {
  this->m_paddle_shader = shader;

  // TODO this shouldn't be here....
  const auto vec = glm::vec2{width, height};
  this->m_block_scale = glm::scale(glm::mat3{1.0}, vec);

  glGenBuffers(1, &this->m_paddle_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_paddle_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 6, m_paddle_vertices.data(), GL_STATIC_DRAW);

  glGenVertexArrays(1, &this->m_paddle_vao);
  glBindVertexArray(this->m_paddle_vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void dxball::PaddleRenderer::render(Paddle& paddle) const {
  const auto translation_matrix = glm::translate(glm::mat3{1.0}, paddle.get_world_position());

  glUseProgram(this->m_paddle_shader);
  glBindVertexArray(this->m_paddle_vao);

  const auto scale_location = glGetUniformLocation(this->m_paddle_shader, "_scale_matrix");
  glUniformMatrix3fv(scale_location, 1, GL_FALSE, &this->m_block_scale[0][0]);

  const auto translation_location = glGetUniformLocation(this->m_paddle_shader, "_translation_matrix");
  glUniformMatrix3fv(translation_location, 1, GL_FALSE, &translation_matrix[0][0]);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}
