#version 430 core

in vec2 out_tex_coord;

uniform sampler2D _positions_texture;
uniform sampler2D _normals_texture;
uniform sampler2D _diffuse_texture;

uniform vec3 _camera_pos;

out vec4 frag_color;

vec3 ambient_light = vec3(0.2);
vec3 light_position = vec3(-122, 59, -58);

vec3 phong(
  vec3 position,
  vec3 normal,
  vec3 light_position,
  vec3 view_position,
  float shininess,
  vec3 diffuse_color
) {
  vec3 ld = normalize(light_position - position);

  float lambertian = clamp(dot(normal, ld), 0.0, 1.0);
  vec3 diffuse_term = lambertian * diffuse_color;

  float specular = 0.0;

  if (lambertian > 0.0) {
    vec3 refl = reflect(-ld, normal);
    vec3 view = normalize(light_position - _camera_pos);
    float angle = max(dot(refl, view), 0.0);
    specular = pow(angle, shininess);
  }

  float d = length(light_position - position);
  float attenuation = 1.0 / (1.0 + 0.0002 * d + 0.0002 * d * d);

  return attenuation * (diffuse_term + vec3(specular));
}

void main() {
  vec3 diffuse_color = texture(_diffuse_texture, out_tex_coord).xyz;
  float shininess = texture(_diffuse_texture, out_tex_coord).w;
  vec3 normal = texture(_normals_texture, out_tex_coord).xyz;
  vec3 position = texture(_positions_texture, out_tex_coord).xyz;

  vec3 p = phong(
    position,
    normal,
    light_position,
    _camera_pos,
    shininess,
    diffuse_color
  );

  frag_color = vec4(p, 1.0);
}
