#version 430 core

in vec2 out_tex_coord;

uniform sampler2D _positions_texture;
uniform sampler2D _normals_texture;
uniform sampler2D _diffuse_texture;
uniform sampler2D _shadow_texture;

uniform vec3 _camera_pos;

uniform mat4 _light_matrix;

out vec4 frag_color;

vec3 ambient_light = vec3(0.2);
vec3 light_position = vec3(-122, 59, -58);

float calc_shadow(vec4 light_space_position) {
  vec3 proj_coords = (light_space_position.xyz / light_space_position.w) * 0.5 + 0.5;
  float closest_depth = texture(_shadow_texture, proj_coords.xy).r;
  float current_depth = proj_coords.z;

  return current_depth > closest_depth ? 1.0 : 0.0;
}

void main() {
  //frag_color = vec4(texture(_normals_texture, out_tex_coord).xyz, 1.0);
  //frag_color = vec4(texture(_diffuse_texture, out_tex_coord).xyz, 1.0);

  vec3 diffuse_color = texture(_diffuse_texture, out_tex_coord).xyz;
  float shininess = texture(_diffuse_texture, out_tex_coord).w;
  vec3 normal = texture(_normals_texture, out_tex_coord).xyz;
  vec3 position = texture(_positions_texture, out_tex_coord).xyz;

  vec4 light_space_position = _light_matrix * vec4(position, 1.0);
  float shadow_term = calc_shadow(light_space_position);

  vec3 ld = normalize(light_position - position);

  float lambertian = clamp(dot(normal, ld), 0.0, 1.0);
  vec3 diffuse_term = lambertian * diffuse_color;
  //vec3 phong = diffuse_term + ambient_light;
  vec3 phong = diffuse_term + shadow_term * ambient_light;

  float specular = 0.0;
  if (lambertian > 0.0) {
    vec3 R = reflect(-ld, normal);
    vec3 V = normalize(light_position - _camera_pos);
    float angle = max(dot(R, V), 0.0);
    specular = pow(angle, shininess);
  }

  frag_color = vec4(phong + (vec3(specular)), 1.0);
  //frag_color = vec4(vec3(phong.xy, shadow_term), 1.0);
}
