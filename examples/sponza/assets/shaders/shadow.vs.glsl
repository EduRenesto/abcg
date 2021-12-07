#version 430 core

layout(location = 0) in vec3 in_position;

uniform mat4 _model_matrix;
uniform mat4 _light_matrix;

void main() {
  mat4 mvp = _light_matrix * _model_matrix;
  gl_Position = mvp * vec4(in_position, 1.0);
}
