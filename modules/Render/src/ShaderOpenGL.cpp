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
    ambientOcclusionUniform = glGetUniformLocation(this->shaderProgram, "ambientOcclusionUniform");
    roughtnessOcclusion = glGetUniformLocation(this->shaderProgram, "roughtnessOcclusion");
    metalic = glGetUniformLocation(this->shaderProgram, "metalic");
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
}
