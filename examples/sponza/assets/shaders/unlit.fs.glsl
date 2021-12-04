#version 430 core

in vec3 out_normal;
in vec2 out_tex_coord;

out vec4 frag_color;

uniform sampler2D _diffuse_tex;

void main() {
  //vec3 col = (out_normal + vec3(1.0)) / 2.0;
  //frag_color = vec4(col, 1.0);

  frag_color = texture(_diffuse_tex, out_tex_coord);
}
