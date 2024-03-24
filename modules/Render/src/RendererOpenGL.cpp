#include "../include/RendererOpenGL.h"
#include "../shaders/include/ColorShader.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <Material.h>
#include <MaterialOpenGL.h>
#include <Shader.h>
#include <vector>

void RendererOpenGL::init() {
    SDL_Log("Initializing [ RendererOpenGL ]");
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[ RendererOpenGL ] Error creating SDL_INIT_VIDEO %s", SDL_GetError());
    }
    this->projection = glm::perspective(45.0f, 1024.0f/720.0f, 0.1f, 100.0f);
    this->camera->viewMatrix = glm::lookAt(this->camera->position,this->camera->point,this->camera->orientation);

    this->window = SDL_CreateWindow("Otro titulo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1278, 720, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 5 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,  8);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,   8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,  8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

    this->gl_context = SDL_GL_CreateContext(this->window);
    if(nullptr == this->gl_context) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error SDL_GL_CreateContext: %s", SDL_GetError());
        exit(0);
    }
    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    const GLenum initCode = glewInit();
    if (initCode != GLEW_OK){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize Glew: %s", (const char*) glewGetErrorString(initCode));
        exit(0);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    this->logSystemInformation();
    SDL_Log("[ RendererOpenGL ]   Initialization complete");
}

void RendererOpenGL::destroy() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
}

#define BUFFER_OFFSET(a) ((void*)(a))

void RendererOpenGL::render() {
    for(auto* renderable : renderables) {
        glUseProgram(renderable->materialOpenGL->shaderOpenGL->shaderProgram);
        renderable->materialOpenGL->shaderOpenGL->useUniformVariables(this, renderable->renderable);

        renderable->materialOpenGL->setTextures();
        glBindVertexArray(renderable->vao);

        glBindBuffer(GL_ARRAY_BUFFER, renderable->vertexVBO);
        glVertexAttribPointer(renderable->materialOpenGL->shaderOpenGL->vertexAttribute,
                              3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
        glEnableVertexAttribArray(renderable->materialOpenGL->shaderOpenGL->vertexAttribute);

        glBindBuffer(GL_ARRAY_BUFFER, renderable->normalVBO);
        glVertexAttribPointer(renderable->materialOpenGL->shaderOpenGL->normalAttribute,
                              3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), BUFFER_OFFSET(0));
        glEnableVertexAttribArray(renderable->materialOpenGL->shaderOpenGL->normalAttribute);

        glBindBuffer(GL_ARRAY_BUFFER, renderable->textureVBO);
        glVertexAttribPointer(renderable->materialOpenGL->shaderOpenGL->uvCoordAttribute,
                              2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), BUFFER_OFFSET(0));
        glEnableVertexAttribArray(renderable->materialOpenGL->shaderOpenGL->uvCoordAttribute);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderable->indexVBO);
        glDrawElements(GL_TRIANGLES, renderable->renderable->index.size(), GL_UNSIGNED_INT, NULL);
    }
    SDL_GL_SwapWindow(this->window);
}

void RendererOpenGL::cleanScreen() {
    glClearColor(0.9f, 0.85f, 0.9f, 1.f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOpenGL::logSystemInformation() {
    SDL_Log("OpenGL Version: %s", glGetString(GL_VERSION));
    SDL_Log("OpenGL Shading Language Version: %s", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
    SDL_Log("OpenGL Vendor: %s", (char *)glGetString(GL_VENDOR));
    SDL_Log("OpenGL Renderer: %s", (char *)glGetString(GL_RENDERER));
}