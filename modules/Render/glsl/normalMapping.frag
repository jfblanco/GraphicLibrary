#version 450 core

layout (location = 0) in vec2 fragmentTextureCoords;
layout (location = 1) in vec4 ambientColorFragment;
layout (location = 2) in vec4 difuseColorFragment;
layout (location = 3) in vec4 specularColorFragment;
layout (location = 4) in vec3 lightPositionFrag;
layout (location = 5) in vec3 viewPositionFrag;
layout (location = 6) in vec3 vertexModelWorld;
layout (location = 7) in vec3 vertexTangentFrag;
layout (location = 8) in mat3 tangBitangNormalMatrix;

layout (location = 0) out vec4 finalColor;

uniform sampler2D albedoUniform;
uniform sampler2D normalUniform;

void main() {
    vec4 objectColor = texture(albedoUniform, fragmentTextureCoords);
    vec3 normalTexel = texture(normalUniform, fragmentTextureCoords).rgb;
    normalTexel = normalize(tangBitangNormalMatrix * (normalTexel * 2.0 - 1.0));

    vec3 lightDirection = normalize(lightPositionFrag - vertexModelWorld);
    vec3 viewDirection = normalize(viewPositionFrag - vertexModelWorld);
    vec3 reflectDirection = reflect(-lightDirection, normalTexel);

    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);
    vec4 finalAmbien = (ambientColorFragment * ambientColorFragment.w);
    vec4 finalDiffuse = (difuseColorFragment * difuseColorFragment.w) * max(dot(normalTexel, lightDirection), 0.0);
    vec4 finalSpecular = (specularColorFragment.w * specularFactor * specularColorFragment);
//    finalColor = vec4(normalTexel, 1.0);
//    finalColor = vec4(abs(normalize(vertexBitangentFrag)), 1.0);
//    finalColor = vec4(vertexTangentFrag, 1.0);
    finalColor = (finalAmbien + finalDiffuse + finalSpecular) * objectColor;
}