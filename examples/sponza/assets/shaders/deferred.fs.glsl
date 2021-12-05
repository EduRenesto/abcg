#version 430 core

in vec2 out_tex_coord;

uniform sampler2D _positions_texture;
uniform sampler2D _normals_texture;
uniform sampler2D _diffuse_texture;

out vec4 frag_color;

void main() {
  //frag_color = vec4(texture(_normals_texture, out_tex_coord).xyz, 1.0);
  frag_color = vec4(texture(_diffuse_texture, out_tex_coord).xyz, 1.0);
}
