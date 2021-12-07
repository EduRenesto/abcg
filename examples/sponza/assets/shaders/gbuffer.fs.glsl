#version 430 core

/*
 * This is the shader responsible for populating the GBuffer.
 * It will take the outputs from the vertex shader and write them
 * into the corresponding texel in the GBuffer.
 */

in vec3 out_position;
in vec3 out_normal;
in vec2 out_tex_coord;

/*
 * These are our binding points into our GBuffer render target.
 * The output at location `i` will be written to the color attachment
 * of binding `i`, i.e., `GL_COLOR_ATTACHMENT0 + i`.
 */
layout(location = 0) out vec4 frag_ws_position;
layout(location = 1) out vec4 frag_normal;
layout(location = 2) out vec4 frag_diffuse_spec;

uniform sampler2D _diffuse_tex;
uniform float _shininess;

void main() {
  /*
   * Just write everything to the textures.
   */
  frag_ws_position = vec4(out_position, 0.0);
  frag_normal = vec4(out_normal, 0.0);
  frag_diffuse_spec = vec4(texture(_diffuse_tex, out_tex_coord).xyz, _shininess);
}