#include "paddle_renderer.hpp"
#include <glm/gtx/matrix_transform_2d.hpp>

dxball::PaddleRenderer::PaddleRenderer(GLuint shader) {
  this->m_paddle_shader = shader;

  glGenBuffers(1, &this->m_paddle_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_paddle_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 6, m_paddle_vertices.data(), GL_STATIC_DRAW);

  glGenVertexArrays(1, &this->m_paddle_vao);
  glBindVertexArray(this->m_paddle_vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void dxball::PaddleRenderer::render(
  Paddle& paddle,
  glm::mat4 &projection_matrix
) const {
  const auto translation_matrix = glm::translate(glm::mat3{1.0}, paddle.get_world_position());
  const auto scale_matrix = glm::scale(glm::mat3{1.0}, paddle.get_scale());

  glUseProgram(this->m_paddle_shader);
  glBindVertexArray(this->m_paddle_vao);

  const auto projection_location = glGetUniformLocation(this->m_paddle_shader, "_projection_matrix");
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, &projection_matrix[0][0]);

  const auto scale_location = glGetUniformLocation(this->m_paddle_shader, "_scale_matrix");
  glUniformMatrix3fv(scale_location, 1, GL_FALSE, &scale_matrix[0][0]);

  const auto translation_location = glGetUniformLocation(this->m_paddle_shader, "_translation_matrix");
  glUniformMatrix3fv(translation_location, 1, GL_FALSE, &translation_matrix[0][0]);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}
