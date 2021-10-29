#include "ball_renderer.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

dxball::BallRenderer::BallRenderer(GLuint shader, float width, float height) {
  this->m_ball_shader = shader;

  // TODO this shouldn't be here....
  const auto vec = glm::vec2{width, height};
  this->m_block_scale = glm::scale(glm::mat3{1.0}, vec);

  glGenBuffers(1, &this->m_ball_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->m_ball_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2, m_ball_vertices.data(), GL_STATIC_DRAW);

  glGenVertexArrays(1, &this->m_ball_vao);
  glBindVertexArray(this->m_ball_vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void dxball::BallRenderer::render(Ball& ball) const noexcept {
  //std::cout << "BallRenderer::render" << std::endl;
  //std::cout << "position: " << glm::to_string(ball.get_position()) << std::endl;
  //std::cout << "velocity: " << glm::to_string(ball.get_velocity()) << std::endl;

  glUseProgram(this->m_ball_shader);
  glBindVertexArray(this->m_ball_vao);

  const auto scale_location = glGetUniformLocation(this->m_ball_shader, "_scale_matrix");
  glUniformMatrix3fv(scale_location, 1, GL_FALSE, &this->m_block_scale[0][0]);

  const auto position_location = glGetUniformLocation(this->m_ball_shader, "_ball_position");
  glUniform2fv(position_location, 1, &ball.get_position()[0]);

  glBindVertexArray(this->m_ball_vao);
  glPointSize(ball.get_radius() * 5000);
  glDrawArrays(GL_POINTS, 0, 1);
}
