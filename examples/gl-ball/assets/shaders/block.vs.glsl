#version 430 core

layout(location = 0) in vec2 in_position;

uniform mat3 _scale_matrix;
uniform mat3 _translation_matrix;
uniform mat4 _projection_matrix;

void main() {
  mat3 model_matrix = _translation_matrix * _scale_matrix;
  vec4 screen_position = vec4(model_matrix * vec3(in_position, 1.0), 1.0);

  gl_Position = _projection_matrix * screen_position;
}
