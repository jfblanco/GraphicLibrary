#include "../include/NormalMappingShader.h"
#include <Light.h>
#include <ShaderOpenGL.h>
#include <RendererOpenGL.h>

NormalMappingShader::NormalMappingShader() = default;

NormalMappingShader::~NormalMappingShader() = default;

void NormalMappingShader::findUniformVariables() {
    ShaderOpenGL::findUniformVariables();
    ambientColor = glGetUniformLocation(this->shaderProgram, "ambientColor");
    diffuseColor = glGetUniformLocation(this->shaderProgram, "difuseColor");
    specularColor = glGetUniformLocation(this->shaderProgram, "specularColor");
    lightPosition = glGetUniformLocation(this->shaderProgram, "lightPosition");
    viewPosition = glGetUniformLocation(this->shaderProgram, "viewPosition");
}

void NormalMappingShader::useUniformVariables(RenderingSystem* _renderingSystem, Renderable* _renderable) {
    ShaderOpenGL::useUniformVariables(_renderingSystem, _renderable);
    glUniform4fv(this->ambientColor, 1, &(this->ambient->color[0]));
    glUniform4fv(this->diffuseColor, 1, &(this->diffuse->color[0]));
    glUniform4fv(this->specularColor, 1, &(this->specular->color[0]));
    glUniform3fv(this->lightPosition, 1, &(this->diffuse->position[0]));
    glUniform3fv(this->viewPosition, 1, &(((RendererOpenGL*)_renderingSystem)->camera->position)[0]);
    glUniform1i(this->albedoUniform, 0);
    glUniform1i(this->normalUniform, 1);
}