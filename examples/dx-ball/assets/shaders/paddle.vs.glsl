#version 430 core

layout(location = 0) in vec2 in_position;

uniform mat3 _scale_matrix;
uniform mat3 _translation_matrix;

void main() {
  mat3 model_matrix = _scale_matrix * _translation_matrix;
  vec3 screen_position = model_matrix * vec3(in_position, 1.0);
  gl_Position = vec4(screen_position.xy, 0.0, 1.0);
}
