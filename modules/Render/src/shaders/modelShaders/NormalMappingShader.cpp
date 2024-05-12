#include <NormalMappingShader.h>
#include <Light.h>
#include <Shader.h>
#include <RendererOpenGL.h>
#include <OpenGLAPI.h>

NormalMappingShader::NormalMappingShader() = default;

NormalMappingShader::~NormalMappingShader() = default;

void NormalMappingShader::findUniformVariables(OpenGLAPI* _openGlApi) {
    Shader::findUniformVariables(_openGlApi);
    ambientColorUBO = _openGlApi->getUniform(&(this->shaderProgram), "ambientColor");
    diffuseColorUBO = _openGlApi->getUniform(&(this->shaderProgram), "difuseColor");
    specularColorUBO = _openGlApi->getUniform(&(this->shaderProgram), "specularColor");
    lightPositionUBO = _openGlApi->getUniform(&(this->shaderProgram), "lightPosition");
    viewPositionUBO = _openGlApi->getUniform(&(this->shaderProgram), "viewPosition");
}

void NormalMappingShader::useUniformVariables(RenderingSystem* _renderingSystem, OpenGLAPI* _openGlApi, Renderable* _renderable) {
    Shader::useUniformVariables(_renderingSystem, _openGlApi, _renderable);
    _openGlApi->sendUniformVector4(&(this->ambientColorUBO), &(this->ambient->color[0]));
    _openGlApi->sendUniformVector4(&(this->diffuseColorUBO), &(this->diffuse->color[0]));
    _openGlApi->sendUniformVector4(&(this->specularColorUBO), &(this->specular->color[0]));
    _openGlApi->sendUniformVector3(&(this->lightPositionUBO), &(this->diffuse->color[0]));
    _openGlApi->sendUniformVector3(&(this->viewPositionUBO), &(((RendererOpenGL*)_renderingSystem)->camera->position)[0]);
    _openGlApi->sendUniformInteger(&(this->albedoUBO), 0);
    _openGlApi->sendUniformInteger(&(this->normalUBO), 1);
}