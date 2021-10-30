#include "ball_renderer.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

dxball::BallRenderer::BallRenderer(GLuint shader) {
  this->m_ball_shader = shader;

  glGenBuffers(1, &this->m_ball_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_ball_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2, m_ball_vertices.data(), GL_STATIC_DRAW);

  glGenVertexArrays(1, &this->m_ball_vao);
  glBindVertexArray(this->m_ball_vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void dxball::BallRenderer::render(
  Ball& ball,
  glm::mat4 &projection_matrix
) const noexcept {
  //std::cout << "BallRenderer::render" << std::endl;
  //std::cout << "position: " << glm::to_string(ball.get_position()) << std::endl;
  //std::cout << "velocity: " << glm::to_string(ball.get_velocity()) << std::endl;

  glUseProgram(this->m_ball_shader);
  glBindVertexArray(this->m_ball_vao);

  const auto projection_location = glGetUniformLocation(this->m_ball_shader, "_projection_matrix");
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, &projection_matrix[0][0]);

  const auto position_location = glGetUniformLocation(this->m_ball_shader, "_ball_position");
  glUniform2fv(position_location, 1, &ball.get_position()[0]);

  glBindVertexArray(this->m_ball_vao);
  glPointSize(ball.get_radius() * 200);
  glDrawArrays(GL_POINTS, 0, 1);
}
