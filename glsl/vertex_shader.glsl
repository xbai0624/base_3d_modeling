#version 150 core

attribute vec4 vertex;
attribute vec3 normal;
attribute vec3 color;

varying vec3 vert;
varying vec3 vertNormal;
varying vec3 vertex_color;
//varying vec3 inputColor;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;
uniform mat3 normalMatrix;

void main(){
    vert = vertex.xyz;
    vertex_color = clamp(color, 0.0, 1.0);
    //inputColor = clamp(color, 0.0, 1.0);
    vertNormal = normalMatrix * normal;
    gl_Position = projMatrix * mvMatrix * vertex;
}
