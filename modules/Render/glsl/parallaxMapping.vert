#version 450 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUVCoord;
layout (location = 3) in vec3 vertexTangent;
layout (location = 4) in vec3 vertexBitangent;

layout (location = 1) out vec4 ambientColorFragment;
layout (location = 2) out vec4 difuseColorFragment;
layout (location = 3) out vec4 specularColorFragment;

layout (location = 4) out vec3 fragmentPosition;
layout (location = 5) out vec2 fragmentTextureCoords;
layout (location = 6) out vec3 tangentLightPosition;
layout (location = 7) out vec3 tangentViewPosition;
layout (location = 8) out vec3 tangentFragmentPosition;

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
    fragmentPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));

    vec3 T = normalize(mat3(modelMatrix) * vertexTangent);
    vec3 B = normalize(mat3(modelMatrix) * vertexBitangent);
    vec3 N = normalize(mat3(modelMatrix) * vertexNormal);
    mat3 TBN = transpose(mat3(T,B,N));

    tangentLightPosition = TBN * lightPosition;
    tangentViewPosition = TBN * viewPosition;
    tangentFragmentPosition = TBN * fragmentPosition;

    ambientColorFragment = ambientColor;
    difuseColorFragment = difuseColor;
    specularColorFragment = specularColor;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
}