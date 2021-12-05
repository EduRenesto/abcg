#version 430 core

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_tex_coord;

out vec2 out_tex_coord;

void main() {
  out_tex_coord = in_tex_coord;
  gl_Position = vec4(in_position, 0.0, 1.0);
}
