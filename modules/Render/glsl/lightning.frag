#version 450 core

layout (location = 0) in vec2 fragmentTextureCoords;
layout (location = 1) in vec3 normalVert;
layout (location = 2) in vec4 ambientColorFragment;
layout (location = 3) in vec4 difuseColorFragment;
layout (location = 4) in vec4 specularColorFragment;
layout (location = 5) in vec3 lightPositionFrag;
layout (location = 6) in vec3 viewPositionFrag;
layout (location = 7) in vec3 vertexModelWorld;

layout (location = 0) out vec4 finalColor;

uniform sampler2D albedoUniform;

void main() {
    //    vec4 objectColor = vec4(0.4, 0.8, 0.3, 1.0);
    vec4 objectColor = texture(albedoUniform, fragmentTextureCoords);
    //finalColor = vec4(lightPositionFrag, 1.0);
    vec3 lightDirection = normalize(lightPositionFrag - vertexModelWorld);
    vec3 viewDirection = normalize(viewPositionFrag - vertexModelWorld);
    vec3 reflectDirection = reflect(-lightDirection, normalVert);

    float specularFactor = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);
    vec4 finalAmbien = (ambientColorFragment * ambientColorFragment.w);
    vec4 finalDiffuse = (difuseColorFragment * difuseColorFragment.w) * max(dot(normalVert, lightDirection), 0.0);
    vec4 finalSpecular = (specularColorFragment.w * specularFactor * specularColorFragment);
    finalColor = (finalAmbien + finalDiffuse + finalSpecular);
}