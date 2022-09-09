#version 150 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

in vec3 vertex_color[];
in float vert_edge_exclude[];

out vec3 inputColor;
out vec3 dist;
uniform vec2 WIN_SCALE;

void main(void)
{
    float MEW = 500.0; // max edge width

    // compute distance
    vec2 p0 = WIN_SCALE * gl_in[0].gl_Position.xy/gl_in[0].gl_Position.w;
    vec2 p1 = WIN_SCALE * gl_in[1].gl_Position.xy/gl_in[1].gl_Position.w;
    vec2 p2 = WIN_SCALE * gl_in[2].gl_Position.xy/gl_in[2].gl_Position.w;
    vec2 v0 = p2 - p1;
    vec2 v1 = p2 - p0;
    vec2 v2 = p1 - p0;
    float area = abs(v1.x*v2.y - v1.y*v2.x);

    dist = vec3(area/length(v0), vert_edge_exclude[1]*MEW, vert_edge_exclude[2]*MEW);
    inputColor = vertex_color[0];
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    dist = vec3(vert_edge_exclude[0]*MEW, area/length(v1), vert_edge_exclude[2]*MEW);
    inputColor = vertex_color[1];
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    dist = vec3(vert_edge_exclude[0]*MEW, vert_edge_exclude[1]*MEW, area/length(v2));
    inputColor = vertex_color[2];
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}
