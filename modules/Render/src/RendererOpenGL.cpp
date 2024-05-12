#include "../include/RendererOpenGL.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <Material.h>
#include <Shader.h>

RendererOpenGL::RendererOpenGL(SDLAPI *_sdlApi, OpenGLAPI *_openGlApi, RenderableFactoryOpenGL* _renderFactory) {
    this->sdlApi = _sdlApi;
    this->openGlApi = _openGlApi;
    this->renderableFactoryOpenGl = _renderFactory;
}

void RendererOpenGL::init() {
    this->sdlApi->infoLog("Initializing %s","[ RendererOpenGL ]");
    this->sdlApi->initSDL();

    this->projection = glm::perspective(45.0f, 1024.0f/720.0f, 0.1f, 100.0f);
    this->camera->viewMatrix = glm::lookAt(this->camera->position,this->camera->point,this->camera->orientation);

    this->window = this->sdlApi->createWindow("Engine", 1278, 720);
    this->sdlApi->preset3DGraphicConstants();

    this->gl_context = this->sdlApi->create3DContext(this->window);
    this->openGlApi->initOpenGL();

    this->logSystemInformation();
    this->sdlApi->infoLog("[ RendererOpenGL ]   Initialization complete");
}

void RendererOpenGL::destroy() {
    this->sdlApi->destroy(this->window);
}

void RendererOpenGL::render() {
    for(auto* renderable : renderables) {
        this->openGlApi->setShaderProgram(renderable->material->shader->shaderProgram);

        renderable->material->shader->useUniformVariables(this, this->openGlApi, renderable);

        renderable->material->setTextures();
        this->openGlApi->setVertexArray(renderable->vao);
        this->openGlApi->draw(renderable->vertexVBO, renderable->material->shader->vertexAttribute,
                              renderable->normalVBO, renderable->material->shader->normalAttribute,
                              renderable->textureVBO, renderable->material->shader->uvCoordAttribute,
                              renderable->bitangentVBO, renderable->material->shader->bitangentAttribute,
                              renderable->tangentVBO, renderable->material->shader->tangentAttribute,
                              renderable->indexVBO, renderable->index.size());

    }
    this->sdlApi->swap(this->window);
}

void RendererOpenGL::cleanScreen() {
    this->openGlApi->clean(0.65f, 0.7f, 0.9f, 1.0f, 1.0f);
}

void RendererOpenGL::logSystemInformation() {
    this->sdlApi->infoLog("OpenGL Version: %s", (char *)glGetString(GL_VERSION));
    this->sdlApi->infoLog("OpenGL Shading Language Version: %s", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
    this->sdlApi->infoLog("OpenGL Vendor: %s", (char *)glGetString(GL_VENDOR));
    this->sdlApi->infoLog("OpenGL Renderer: %s", (char *)glGetString(GL_RENDERER));
}