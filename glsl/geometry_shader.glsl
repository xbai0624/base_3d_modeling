#version 150 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec3 vertex_color[];
out vec3 inputColor;

out vec3 dist;
uniform vec2 WIN_SCALE;

void main(void)
{
    // compute distance
    vec2 p0 = WIN_SCALE * gl_in[0].gl_Position.xy/gl_in[0].gl_Position.w;
    vec2 p1 = WIN_SCALE * gl_in[1].gl_Position.xy/gl_in[1].gl_Position.w;
    vec2 p2 = WIN_SCALE * gl_in[2].gl_Position.xy/gl_in[2].gl_Position.w;
    vec2 v0 = p2 - p1;
    vec2 v1 = p2 - p0;
    vec2 v2 = p1 - p0;
    float area = abs(v1.x*v2.y - v1.y*v2.x);

    dist = vec3(area/length(v0), 0, 0);
    inputColor = vertex_color[0];
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    dist = vec3(0, area/length(v1), 0);
    inputColor = vertex_color[1];
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    dist = vec3(0, 0, area/length(v2));
    inputColor = vertex_color[2];
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}
