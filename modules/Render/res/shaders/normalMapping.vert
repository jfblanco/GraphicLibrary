#version 450 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUVCoord;

layout (location = 0) out vec2 fragmentTextureCoords;
layout (location = 1) out vec4 ambientColorFragment;
layout (location = 2) out vec4 difuseColorFragment;
layout (location = 3) out vec4 specularColorFragment;
layout (location = 4) out vec3 lightPositionFrag;
layout (location = 5) out vec3 viewPositionFrag;
layout (location = 6) out vec3 vertexModelWorld;
layout (location = 7) out mat4 modelMatrixWorld;

uniform vec4 difuseColor;
uniform vec4 specularColor;
uniform vec4 ambientColor;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main() {
    fragmentTextureCoords = vertexUVCoord;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);

    lightPositionFrag = lightPosition;
    vertexModelWorld = vec3(modelMatrix * vec4(vertexPosition, 1.0));
    modelMatrixWorld = modelMatrix;

    viewPositionFrag = viewPosition;
    ambientColorFragment = ambientColor;
    difuseColorFragment = difuseColor;
    specularColorFragment = specularColor;
}