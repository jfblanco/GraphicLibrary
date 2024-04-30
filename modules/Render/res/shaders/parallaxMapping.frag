#version 450 core

layout (location = 0) in vec2 fragmentTextureCoords;
layout (location = 1) in vec4 ambientColorFragment;
layout (location = 2) in vec4 difuseColorFragment;
layout (location = 3) in vec4 specularColorFragment;
layout (location = 4) in vec3 lightPositionFrag;
layout (location = 5) in vec3 viewPositionFrag;
layout (location = 6) in vec3 vertexModelWorld;
layout (location = 7) in vec3 vertexTangentFrag;

layout (location = 8) in vec3 tangentLightPosition;
layout (location = 9) in vec3 tangentViewPosition;
layout (location = 10) in vec3 tangentFragmentPosition;
layout (location = 11) in vec3 fragmentPosition;
layout (location = 12) in mat3 tangBitangNormalMatrix;

layout (location = 0) out vec4 finalColor;

uniform sampler2D albedoUniform;
uniform sampler2D normalUniform;
uniform sampler2D heightUniform;

uniform float heightScale;

vec2 ParallaxMapping(vec2 texCoords, vec3 directionalMapping);

void main() {
    vec3 viewDirNormalized = normalize(tangentViewPosition - tangentFragmentPosition);
    vec2 paralaxTexCoords = ParallaxMapping(fragmentTextureCoords, viewDirNormalized);
    if(paralaxTexCoords.x > 1.0 || paralaxTexCoords.y > 1.0 || paralaxTexCoords.x < 0.0 || paralaxTexCoords.y < 0.0)
        discard;

    vec4 objectColor = texture(albedoUniform, paralaxTexCoords);
    vec3 normalTexel = texture(normalUniform, paralaxTexCoords).rgb;

    normalTexel = normalize(normalTexel * 2.0 - 1.0);
//    normalTexel = normalize(tangBitangNormalMatrix * (normalTexel * 2.0 - 1.0));

    vec3 lightDirection = normalize(lightPositionFrag - vertexModelWorld);
    vec3 viewDirection = normalize(viewPositionFrag - vertexModelWorld);
    vec3 reflectDirection = reflect(-lightDirection, normalTexel);

    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);
    vec4 finalAmbien = (ambientColorFragment * ambientColorFragment.w);
    vec4 finalDiffuse = (difuseColorFragment * difuseColorFragment.w) * max(dot(normalTexel, lightDirection), 0.0);
    vec4 finalSpecular = (specularColorFragment.w * specularFactor * specularColorFragment);

    finalColor = (finalAmbien + finalDiffuse + finalSpecular) * objectColor;
//    finalColor = texCoords;
}

//vec4 ParallaxMapping(vec2 texCoords, vec3 viewDir) {
//    return texture(heightUniform, texCoords);
//}

// Function 1, it is simple, but it is not the best approach
//vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir) {
//    float height =  texture(heightUniform, texCoords).r;
//    vec2 p = viewDir.xy / viewDir.z * (height * heightScale);
//    return texCoords - p;
//}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir) {
    const float numberOfLayers = 10;
    float layerDepth = 1.0 / numberOfLayers;
    float currentLayerDepth = 0.0;

    vec2 p = viewDir.xy * heightScale;
    vec2 deltaTextCoords = p / numberOfLayers;

    vec2 currentTextureCoords = texCoords;
    float currentDepthMapValue = texture(heightUniform, currentTextureCoords).r;

    while(currentLayerDepth < currentDepthMapValue) {
        currentTextureCoords -= deltaTextCoords;
        currentDepthMapValue = texture(heightUniform, currentTextureCoords).r;
        currentLayerDepth += layerDepth;
    }

    vec2 prevTexCoords = currentTextureCoords + deltaTextCoords;

    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(heightUniform, prevTexCoords).r - currentLayerDepth + layerDepth;

    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTextureCoords * (1.0 - weight);

    return finalTexCoords;
}