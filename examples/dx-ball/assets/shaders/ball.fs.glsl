#version 430 core

out vec4 out_frag_color;

vec4 ball_color = vec4(0.42352941, 0.44313725, 0.76862745, 1.0);

void main() {
  vec2 point_to_center = vec2(0.5) - gl_PointCoord;

  if (length(point_to_center) < 0.50) {
    out_frag_color = ball_color;
  } else {
    out_frag_color = vec4(0.0);
  }
}
