#version 460 core

layout (location = 0) in vec3 vFragPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec4 FragColor;

void main(){
    FragColor = vec4(1.0);
}


