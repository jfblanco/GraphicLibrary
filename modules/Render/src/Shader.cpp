#include <Shader.h>
#include <OpenGLAPI.h>
#include <RendererOpenGL.h>
#include <glm/gtc/type_ptr.hpp>

void Shader::findUniformVariables(OpenGLAPI *_openGLApi) {
    projectionModelViewUniform = _openGLApi->getUniform(&(this->shaderProgram), "projectionMatrix");
    modelMatrixUniform = _openGLApi->getUniform(&(this->shaderProgram), "modelMatrix");
    viewMatrixUniform = _openGLApi->getUniform(&(this->shaderProgram), "viewMatrix");

    albedoUBO = _openGLApi->getUniform(&(this->shaderProgram), "albedoUniform");
    normalUBO = _openGLApi->getUniform(&(this->shaderProgram), "normalUniform");
    heightUBO = _openGLApi->getUniform(&(this->shaderProgram), "heightUniform");
    ambientOcclusionUBO = _openGLApi->getUniform(&(this->shaderProgram), "ambientOcclusionUniform");
    roughtnessOcclusionUBO = _openGLApi->getUniform(&(this->shaderProgram), "roughtnessOcclusionUniform");
    metallicUBO = _openGLApi->getUniform(&(this->shaderProgram), "metallicUniform");
}

void Shader::useUniformVariables(RenderingSystem* _renderSystem, OpenGLAPI* _openGlApi, Renderable* _renderable) {
    _openGlApi->sendUniformMatrix(&(this->projectionModelViewUniform), glm::value_ptr(((RendererOpenGL*)_renderSystem)->projection));
    _openGlApi->sendUniformMatrix(&(this->viewMatrixUniform), glm::value_ptr(((RendererOpenGL*)_renderSystem)->camera->viewMatrix));
    _openGlApi->sendUniformMatrix(&(this->modelMatrixUniform), glm::value_ptr(_renderable->modelMatrix));
}

void Shader::findVertexAttributeVariables(OpenGLAPI *_openGLApi) {
    vertexAttribute = _openGLApi->getAttribute(&(this->shaderProgram), "vertexPosition");
    normalAttribute = _openGLApi->getAttribute(&(this->shaderProgram), "vertexNormal");
    uvCoordAttribute = _openGLApi->getAttribute(&(this->shaderProgram), "vertexUVCoord");
    tangentAttribute = _openGLApi->getAttribute(&(this->shaderProgram), "vertexTangent");
    bitangentAttribute = _openGLApi->getAttribute(&(this->shaderProgram), "vertexBitangent");
}
