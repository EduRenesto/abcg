#version 430 core

uniform float _block_life;

out vec4 out_frag_color;

vec4 dead_color = vec4(0.02745098, 0.21176471, 0.25882353, 1.0);
vec4 alive_color = vec4(0.57647059, 0.63137255, 0.63137255, 1.0);

void main() {
   out_frag_color = mix(dead_color, alive_color, _block_life);
}
