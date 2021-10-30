#version 430 core

layout(location = 0) in vec2 in_position;

uniform vec2 _ball_position;
uniform mat4 _projection_matrix;

uniform float _point_size;

void main() {
  vec3 indexed_position = vec3(_ball_position + in_position, 0);

  gl_PointSize = _point_size;
  gl_Position = _projection_matrix * vec4(indexed_position.xyz, 1.0);
}
