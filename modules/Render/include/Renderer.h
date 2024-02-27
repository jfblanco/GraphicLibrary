//
// Created by Francisco Blanco on 12/28/2023.
//

#ifndef ENGINETEST_RENDERER_H
#define ENGINETEST_RENDERER_H

#include <SDL3/SDL.h>
#include <RenderingSystem.h>

class Renderer : public RenderingSystem {
private:
    void logSystemInformation();
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext gl_context = nullptr;

    Renderer()=default;
    ~Renderer()=default;

    void init() override;
    void destroy() override;
    void render() override;
    void cleanScreen() override;
};


#endif //ENGINETEST_RENDERER_H
