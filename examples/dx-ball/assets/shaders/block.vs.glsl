#version 430 core

layout(location = 0) in vec2 in_position;

uniform mat3 _scale_matrix;
uniform ivec2 _block_position;

void main() {
  vec3 indexed_position = vec3(_block_position + in_position, 0);

  vec3 scaled = _scale_matrix * indexed_position;

  gl_Position = vec4(scaled.xy, 0.0, 1.0);
}
