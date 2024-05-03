#include "../include/Shader.h"
#include "../include/RendererOpenGL.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

void Shader::findUniformVariables() {
    projectionModelViewUniform = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
    modelMatrixUniform = glGetUniformLocation(this->shaderProgram, "modelMatrix");
    viewMatrixUniform = glGetUniformLocation(this->shaderProgram, "viewMatrix");

    albedoUBO = glGetUniformLocation(this->shaderProgram, "albedoUniform");
    normalUBO = glGetUniformLocation(this->shaderProgram, "normalUniform");
    heightUBO = glGetUniformLocation(this->shaderProgram, "heightUniform");
    ambientOcclusionUBO = glGetUniformLocation(this->shaderProgram, "ambientOcclusionUniform");
    roughtnessOcclusionUBO = glGetUniformLocation(this->shaderProgram, "roughtnessOcclusionUniform");
    metallicUBO = glGetUniformLocation(this->shaderProgram, "metallicUniform");
}

void Shader::useUniformVariables(RenderingSystem* _renderSystem, Renderable* _renderable) {
    glUniformMatrix4fv(this->projectionModelViewUniform, 1, GL_FALSE, glm::value_ptr(((RendererOpenGL*)_renderSystem)->projection));
    glUniformMatrix4fv(this->viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(((RendererOpenGL*)_renderSystem)->camera->viewMatrix));
    glUniformMatrix4fv(this->modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(_renderable->modelMatrix));
}

void Shader::findVertexAttributeVariables() {
    vertexAttribute = glGetAttribLocation(this->shaderProgram, "vertexPosition");
    normalAttribute = glGetAttribLocation(this->shaderProgram, "vertexNormal");
    uvCoordAttribute = glGetAttribLocation(this->shaderProgram, "vertexUVCoord");
    tangentAttribute = glGetAttribLocation(this->shaderProgram, "vertexTangent");
    bitangentAttribute = glGetAttribLocation(this->shaderProgram, "vertexBitangent");
}
