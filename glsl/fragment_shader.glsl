#version 150 core

varying highp vec3 vert;
varying highp vec3 vertNormal;
varying highp vec3 inputColor;

varying highp vec3 dist;

uniform highp vec3 lightPos;

void main(){
    float nearD = min(min(dist[0], dist[1]), dist[2]);
    float edgeIntensity = exp2(-1.0 * nearD * nearD);

    highp vec3 L = normalize(lightPos - vert);
    highp float NL = max(dot(normalize(vertNormal), L), 0.0);
    //highp vec3 color = vec3(0.39, 1.0, 0.0);
    highp vec3 color = inputColor;
    //highp vec3 col = clamp(color*0.2 /*ambient light part*/ + color*0.8*NL /*diffuse light part*/, 0.0, 1.0);
    //highp vec3 col = clamp(color*0.35 + color*0.65*NL, 0.0, 1.0);

    highp vec3 col = color;
    gl_FragColor = (1.-edgeIntensity) * vec4(col, 1.0);
}
