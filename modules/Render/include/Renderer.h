//
// Created by Francisco Blanco on 12/28/2023.
//

#ifndef ENGINETEST_RENDERER_H
#define ENGINETEST_RENDERER_H

#include <SDL3/SDL.h>

class Renderer {
private:
    void logSystemInformation();
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext gl_context = nullptr;

    Renderer()=default;
    ~Renderer()=default;

    void init();
    void render();
    void cleanScreen();
};


#endif //ENGINETEST_RENDERER_H
