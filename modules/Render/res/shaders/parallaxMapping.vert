#version 450 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;
layout (location = 2) in vec2 vertexUVCoord;
layout (location = 3) in vec3 vertexTangent;
layout (location = 4) in vec3 vertexBitangent;

layout (location = 0) out vec2 fragmentTextureCoords;
layout (location = 1) out vec4 ambientColorFragment;
layout (location = 2) out vec4 difuseColorFragment;
layout (location = 3) out vec4 specularColorFragment;
layout (location = 4) out vec3 lightPositionFrag;
layout (location = 5) out vec3 viewPositionFrag;
layout (location = 6) out vec3 vertexModelWorld;
layout (location = 7) out vec3 vertexTangentFrag;

layout (location = 8) out vec3 tangentLightPosition;
layout (location = 9) out vec3 tangentViewPosition;
layout (location = 10) out vec3 tangentFragmentPosition;
layout (location = 11) out vec3 fragmentPosition;
layout (location = 12) out mat3 tangBitangNormalMatrix;

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
    fragmentPosition = vec3(modelMatrix * vec4(vertexPosition, 1.0));

    lightPositionFrag = lightPosition;
    vertexModelWorld = vec3(modelMatrix * vec4(vertexPosition, 1.0));

    vec3 T = normalize(vec3(modelMatrix * vec4(vertexTangent, 0.0)));
    vec3 B = normalize(vec3(modelMatrix * vec4(vertexBitangent, 0.0)));
    vec3 N = normalize(vec3(modelMatrix * vec4(vertexNormal, 0.0)));

    mat3 TBN = mat3(T,B,N);

    tangBitangNormalMatrix = TBN;

    tangentLightPosition = TBN * lightPosition;
    tangentViewPosition = TBN * viewPosition;
    tangentFragmentPosition = TBN * fragmentPosition;

    vertexTangentFrag = vertexTangent;

    viewPositionFrag = viewPosition;
    ambientColorFragment = ambientColor;
    difuseColorFragment = difuseColor;
    specularColorFragment = specularColor;
}