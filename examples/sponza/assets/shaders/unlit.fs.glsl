#version 430 core

in vec3 out_normal;
in vec2 out_tex_coord;
in flat int out_material_index;

uniform sampler2D _textures[80];

out vec4 frag_color;

void main() {
  //vec3 col = (out_normal + vec3(1.0)) / 2.0;
  vec3 col = texture(_textures[out_material_index], out_tex_coord);
  frag_color = vec4(col, 1.0);
}
