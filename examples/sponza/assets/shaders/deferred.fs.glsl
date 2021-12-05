#version 430 core

in vec2 out_tex_coord;

uniform sampler2D _positions_texture;
uniform sampler2D _normals_texture;
uniform sampler2D _diffuse_texture;

out vec4 frag_color;

vec3 ambient_light = vec3(0.2);
vec3 light_position = vec3(-122, 59, -58);

void main() {
  //frag_color = vec4(texture(_normals_texture, out_tex_coord).xyz, 1.0);
  //frag_color = vec4(texture(_diffuse_texture, out_tex_coord).xyz, 1.0);

  vec3 diffuse_color = texture(_diffuse_texture, out_tex_coord).xyz;
  vec3 normal = texture(_normals_texture, out_tex_coord).xyz;
  vec3 position = texture(_positions_texture, out_tex_coord).xyz;

  vec3 ld = normalize(light_position - position);

  float coeff = clamp(dot(normal, ld), 0, 1);
  vec3 diffuse_term = coeff * diffuse_color;
  vec3 phong = diffuse_term + ambient_light;

  frag_color = vec4(phong, 1.0);
}
