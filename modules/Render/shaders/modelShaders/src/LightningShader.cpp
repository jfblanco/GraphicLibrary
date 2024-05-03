#include "../include/LightningShader.h"
#include "../include/RendererOpenGL.h"
#include <Light.h>

void LightningShader::findUniformVariables() {
    Shader::findUniformVariables();
    ambientColorUBO = glGetUniformLocation(this->shaderProgram, "ambientColor");
    diffuseColorUBO = glGetUniformLocation(this->shaderProgram, "difuseColor");
    specularColorUBO = glGetUniformLocation(this->shaderProgram, "specularColor");
    lightPositionUBO = glGetUniformLocation(this->shaderProgram, "lightPosition");
    viewPositionUBO = glGetUniformLocation(this->shaderProgram, "viewPosition");
}

void LightningShader::useUniformVariables(RenderingSystem* _renderingSystem, Renderable* _renderable) {
    Shader::useUniformVariables(_renderingSystem, _renderable);
    glUniform4fv(this->ambientColorUBO, 1, &(this->ambient->color[0]));
    glUniform4fv(this->diffuseColorUBO, 1, &(this->diffuse->color[0]));
    glUniform4fv(this->specularColorUBO, 1, &(this->specular->color[0]));
    glUniform3fv(this->lightPositionUBO, 1, &(this->diffuse->position[0]));
    glUniform3fv(this->viewPositionUBO, 1, &(((RendererOpenGL*)_renderingSystem)->camera->position)[0]);
}