#version 450 core

layout (location = 0) out vec3 color;

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUVCoord;

uniform mat4 projectionMatrix;

void main() {
    color = vec3(1.0, 0.0, 0.0);
    gl_Position = projectionMatrix * vec4(vertexPosition, 1.0);
}