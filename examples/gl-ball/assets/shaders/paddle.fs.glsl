#version 430 core

out vec4 out_frag_color;

vec4 paddle_color = vec4(0.82745098, 0.21176471, 0.50980392, 1.0);

void main() {
   out_frag_color = paddle_color;
}
