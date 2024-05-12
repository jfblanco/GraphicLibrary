#include <LightningShader.h>
#include <RendererOpenGL.h>
#include <OpenGLAPI.h>
#include <Light.h>

void LightningShader::findUniformVariables(OpenGLAPI* _openGLApi) {
    Shader::findUniformVariables(_openGLApi);
    ambientColorUBO = _openGLApi->getUniform(&(this->shaderProgram), "ambientColor");
    diffuseColorUBO = _openGLApi->getUniform(&(this->shaderProgram), "difuseColor");
    specularColorUBO = _openGLApi->getUniform(&(this->shaderProgram), "specularColor");
    lightPositionUBO = _openGLApi->getUniform(&(this->shaderProgram), "lightPosition");
    viewPositionUBO = _openGLApi->getUniform(&(this->shaderProgram), "viewPosition");
}

void LightningShader::useUniformVariables(RenderingSystem* _renderingSystem, OpenGLAPI* _openGlApi, Renderable* _renderable) {
    Shader::useUniformVariables(_renderingSystem, _openGlApi, _renderable);
    _openGlApi->sendUniformVector4(&(this->ambientColorUBO), &(this->ambient->color[0]));
    _openGlApi->sendUniformVector4(&(this->diffuseColorUBO), &(this->diffuse->color[0]));
    _openGlApi->sendUniformVector4(&(this->specularColorUBO), &(this->specular->color[0]));
    _openGlApi->sendUniformVector3(&(this->lightPositionUBO), &(this->diffuse->color[0]));
    _openGlApi->sendUniformVector3(&(this->viewPositionUBO), &(((RendererOpenGL*)_renderingSystem)->camera->position)[0]);
}