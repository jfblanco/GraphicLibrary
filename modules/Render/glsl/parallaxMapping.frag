#version 450 core

layout (location = 1) in vec4 ambientColorFragment;
layout (location = 2) in vec4 difuseColorFragment;
layout (location = 3) in vec4 specularColorFragment;

layout (location = 4) in vec3 fragmentPosition;
layout (location = 5) in vec2 fragmentTextureCoords;
layout (location = 6) in vec3 tangentLightPosition;
layout (location = 7) in vec3 tangentViewPosition;
layout (location = 8) in vec3 tangentFragmentPosition;

layout (location = 0) out vec4 finalColor;

uniform sampler2D albedoUniform;
uniform sampler2D normalUniform;
uniform sampler2D heightUniform;

uniform float heightScale;

vec2 ParallaxMapping(vec2 texCoords, vec3 directionalMapping);

void main() {
    vec3 viewDirNormalized = normalize(tangentViewPosition - tangentFragmentPosition);
    vec2 paralaxTexCoords = ParallaxMapping(fragmentTextureCoords, viewDirNormalized);

    vec4 objectColor = texture(albedoUniform, paralaxTexCoords);
    vec3 normalTexel = texture(normalUniform, paralaxTexCoords).rgb;

    normalTexel = normalize(normalTexel * 2.0 - 1.0);

    vec3 lightDirection = normalize(tangentLightPosition - tangentFragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normalTexel);
    vec3 lightMiddleVector = normalize(lightDirection + viewDirNormalized);

    float specularFactor = pow(max(dot(normalTexel, reflectDirection), 0.0), 32);
    vec4 finalAmbien = (ambientColorFragment * ambientColorFragment.w);
    vec4 finalDiffuse = (difuseColorFragment * difuseColorFragment.w) * max(dot(normalTexel, lightDirection), 0.0);
    vec4 finalSpecular = (specularColorFragment.w * specularFactor * specularColorFragment);

    if(paralaxTexCoords.x > 1.0 || paralaxTexCoords.y > 1.0 || paralaxTexCoords.x < 0.0 || paralaxTexCoords.y < 0.0) {
        discard;
    } else {
        finalColor = ((finalAmbien + finalDiffuse) * objectColor) * 0.8 + finalSpecular * 0.2;
    }
}

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir) {
    const float minLayers = 15.0;
    const float maxLayers = 50.0;
    float numberOfLayers = mix(maxLayers, minLayers, max(dot(vec3(0.0, 0.0, 1.0), viewDir), 0.0));

    float layerDepth = 1.0 / numberOfLayers;
    float currentLayerDepth = 0.0;

    vec2 p = viewDir.xy / viewDir.z * heightScale;
    vec2 deltaTextCoords = p / numberOfLayers;

    vec2 currentTextureCoords = texCoords;
    float currentDepthMapValue = 1.0 - texture(heightUniform, currentTextureCoords).r;

    while(currentLayerDepth < currentDepthMapValue) {
        currentTextureCoords -= deltaTextCoords;
        currentDepthMapValue = 1.0 - texture(heightUniform, currentTextureCoords).r;
        currentLayerDepth += layerDepth;
    }

    vec2 prevTexCoords = currentTextureCoords + deltaTextCoords;

    float afterDepth  = currentDepthMapValue.r - currentLayerDepth;
    float beforeDepth = (1.0 - texture(heightUniform, prevTexCoords).r) - currentLayerDepth + layerDepth;

    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTextureCoords * (1.0 - weight);

    return finalTexCoords;
}