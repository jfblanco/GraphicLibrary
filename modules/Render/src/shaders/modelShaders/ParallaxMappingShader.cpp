#include <ParallaxMappingShader.h>
#include <Light.h>
#include <Shader.h>
#include <RendererOpenGL.h>
#include <OpenGLAPI.h>

ParallaxMappingShader::ParallaxMappingShader() = default;

ParallaxMappingShader::~ParallaxMappingShader() = default;

void ParallaxMappingShader::findUniformVariables(OpenGLAPI* _openGlApi) {
    Shader::findUniformVariables(_openGlApi);
    ambientColorUBO = _openGlApi->getUniform(&(this->shaderProgram), "ambientColor");
    diffuseColorUBO = _openGlApi->getUniform(&(this->shaderProgram), "difuseColor");
    specularColorUBO = _openGlApi->getUniform(&(this->shaderProgram), "specularColor");
    lightPositionUBO = _openGlApi->getUniform(&(this->shaderProgram), "lightPosition");
    viewPositionUBO = _openGlApi->getUniform(&(this->shaderProgram), "viewPosition");
    heightScaleUniform = _openGlApi->getUniform(&(this->shaderProgram), "heightScale");
}

void ParallaxMappingShader::useUniformVariables(RenderingSystem* _renderingSystem, OpenGLAPI* _openGlApi, Renderable* _renderable) {
    Shader::useUniformVariables(_renderingSystem, _openGlApi, _renderable);
    _openGlApi->sendUniformVector4(&(this->ambientColorUBO), &(this->ambient->color[0]));
    _openGlApi->sendUniformVector4(&(this->diffuseColorUBO), &(this->diffuse->color[0]));
    _openGlApi->sendUniformVector4(&(this->specularColorUBO), &(this->specular->color[0]));
    _openGlApi->sendUniformVector3(&(this->lightPositionUBO), &(this->diffuse->position[0]));
    _openGlApi->sendUniformVector3(&(this->viewPositionUBO), &(((RendererOpenGL*)_renderingSystem)->camera->position)[0]);

    _openGlApi->sendUniformFloat(&(this->heightScaleUniform), this->heightScale);
    _openGlApi->sendUniformInteger(&(this->albedoUBO), 0);
    _openGlApi->sendUniformInteger(&(this->normalUBO), 1);
    _openGlApi->sendUniformInteger(&(this->heightUBO), 2);
}