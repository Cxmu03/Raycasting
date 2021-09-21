#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;

out vec3 vColor;

void main() {
    gl_Position = vec4(vertexPosition.xyz, 1.f);
    vColor = vertexColor;
}