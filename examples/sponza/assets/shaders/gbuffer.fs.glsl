#version 430 core

in vec3 out_position;
in vec3 out_normal;
in vec2 out_tex_coord;

layout(location = 0) out vec4 frag_ws_position;
layout(location = 1) out vec4 frag_normal;
layout(location = 2) out vec4 frag_diffuse_spec;

uniform sampler2D _diffuse_tex;
uniform float _shininess;

void main() {
  frag_ws_position = vec4(out_position, 0.0);
  frag_normal = vec4(out_normal, 0.0);
  frag_diffuse_spec = vec4(texture(_diffuse_tex, out_tex_coord).xyz, _shininess);
}