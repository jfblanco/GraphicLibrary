#version 450 core

layout (location = 0) in vec2 fragmentTextureCoords;
layout (location = 0) out vec4 finalColor;

uniform sampler2D albedoUniform;

void main() {
    finalColor = texture(albedoUniform, fragmentTextureCoords);
}