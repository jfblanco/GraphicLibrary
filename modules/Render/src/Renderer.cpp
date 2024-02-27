//
// Created by Francisco Blanco on 12/28/2023.
//

#include "../include/Renderer.h"
#include <SDL3/SDL.h>
#include <glad.h>

void Renderer::init() {
    SDL_Log("Initializing [Renderer]");
    this->window = SDL_CreateWindow("Otro titulo", 1024, 720, SDL_WINDOW_OPENGL);
    this->renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

    if(NULL == (this->gl_context = SDL_GL_CreateContext(this->window))) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error SDL_GL_CreateContext: %s", SDL_GetError());
    }
    else SDL_GL_MakeCurrent(this->window, this->gl_context);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error Initializing GLAD: %s", glad_glGetError());
    }
    this->logSystemInformation();
    SDL_Log("Renderer initialization complete!!!");
}

void Renderer::destroy() {
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
}

void Renderer::render() {
    SDL_GL_SwapWindow(this->window);
}

void Renderer::cleanScreen() {
    glClearColor(0.8f, 0.9f, 0.8f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Renderer::logSystemInformation() {

    SDL_Log("OpenGL Version: %d.%d", GLVersion.major, GLVersion.minor);
    SDL_Log("OpenGL Shading Language Version: %s", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
    SDL_Log("OpenGL Vendor: %s", (char *)glGetString(GL_VENDOR));
    SDL_Log("OpenGL Renderer: %s", (char *)glGetString(GL_RENDERER));
}