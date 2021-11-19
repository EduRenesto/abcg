#version 430 core

in vec3 out_normal;

out vec4 frag_color;

void main() {
  vec3 col = (out_normal + vec3(1.0)) / 2.0;
  frag_color = vec4(col, 1.0);
}
