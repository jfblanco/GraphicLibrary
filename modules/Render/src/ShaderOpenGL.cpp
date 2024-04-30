#include "../include/ShaderOpenGL.h"
#include "../include/RendererOpenGL.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

void ShaderOpenGL::findUniformVariables() {
    projectionModelViewUniform = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
    modelMatrixUniform = glGetUniformLocation(this->shaderProgram, "modelMatrix");
    viewMatrixUniform = glGetUniformLocation(this->shaderProgram, "viewMatrix");

    albedoUniform = glGetUniformLocation(this->shaderProgram, "albedoUniform");
    normalUniform = glGetUniformLocation(this->shaderProgram, "normalUniform");
    heightUniform = glGetUniformLocation(this->shaderProgram, "heightUniform");
    ambientOcclusionUniform = glGetUniformLocation(this->shaderProgram, "ambientOcclusionUniform");
    roughtnessOcclusionUniform = glGetUniformLocation(this->shaderProgram, "roughtnessOcclusionUniform");
    metallicUniform = glGetUniformLocation(this->shaderProgram, "metallicUniform");
}

void ShaderOpenGL::useUniformVariables(RenderingSystem* _renderSystem, Renderable* _renderable) {
    glUniformMatrix4fv(this->projectionModelViewUniform, 1, GL_FALSE, glm::value_ptr(((RendererOpenGL*)_renderSystem)->projection));
    glUniformMatrix4fv(this->viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(((RendererOpenGL*)_renderSystem)->camera->viewMatrix));
    glUniformMatrix4fv(this->modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(_renderable->modelMatrix));
}

void ShaderOpenGL::findVertexAttributeVariables() {
    vertexAttribute = glGetAttribLocation(this->shaderProgram, "vertexPosition");
    normalAttribute = glGetAttribLocation(this->shaderProgram, "vertexNormal");
    uvCoordAttribute = glGetAttribLocation(this->shaderProgram, "vertexUVCoord");
    tangentAttribute = glGetAttribLocation(this->shaderProgram, "vertexTangent");
    bitangentAttribute = glGetAttribLocation(this->shaderProgram, "vertexBitangent");
}
