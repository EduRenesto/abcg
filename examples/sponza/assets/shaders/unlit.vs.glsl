#version 430 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex_coord;

out vec3 out_normal;
out vec2 out_tex_coord;

uniform mat4 _model_matrix;
uniform mat4 _view_matrix;
uniform mat4 _projection_matrix;

void main() {
  mat4 mvp = _projection_matrix * _view_matrix * _model_matrix;
  gl_Position = mvp * vec4(in_position, 1.0);

  out_normal = in_normal;
  out_tex_coord = in_tex_coord;

  out_normal = vec3(in_tex_coord, 0.0);
}
