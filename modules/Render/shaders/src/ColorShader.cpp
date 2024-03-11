#include "../include/ColorShader.h"
#include "../include/RendererOpenGL.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

void ColorShader::findUniformVariables() {
    projectionModelViewUniform = glGetUniformLocation(this->shaderProgram, "projectionMatrix");
}

void ColorShader::useUniformVariables(RenderingSystem* _renderSystem) {
    glm::mat4x4 projView = ((RendererOpenGL*)_renderSystem)->projection * ((RendererOpenGL*)_renderSystem)->camera->viewMatrix;
    glUniformMatrix4fv(this->projectionModelViewUniform, 1, GL_FALSE, glm::value_ptr(projView));
}

void ColorShader::findVertexAttributeVariables() {
    vertexAttribute = glGetAttribLocation(this->shaderProgram, "vertexPosition");
    normalAttribute = glGetAttribLocation(this->shaderProgram, "vertexNormal");
    uvCoordAttribute = glGetAttribLocation(this->shaderProgram, "vertexUVCoord");
}
