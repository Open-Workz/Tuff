#version 460 core

const vec3 Pos[4] = vec3[](
    vec3(-1.0, 0.0, -1.0),
    vec3(1.0, 0.0, -1.0),
    vec3(1.0, 0.0, 1.0),
    vec3(-1.0, 0.0, 1.0)
);

const int Indices[6] = int[](0, 2, 1, 2, 0, 3);

uniform mat4 uView;
uniform mat4 uProjection;
uniform vec3 uViewPosition;
uniform float uGridSize;

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out float vGridSize;
layout(location = 2) out vec3 vViewWorldPos;

void main(){
    mat4 viewProjection = uProjection * uView;
    int index = Indices[gl_VertexID];
    vec3 vPos3 = Pos[index] * uGridSize;
    vPos3.x += uViewPosition.x;
    vPos3.y = 0.0;
    vPos3.z += uViewPosition.z;
    vec4 vPos4 = vec4(vPos3, 1.0);
    gl_Position = viewProjection * vPos4;
    vWorldPos = vPos3;
    vGridSize = uGridSize;
    vViewWorldPos = uViewPosition;
}