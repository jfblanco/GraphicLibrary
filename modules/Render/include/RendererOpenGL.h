#ifndef ENGINETEST_RENDEREROPENGL_H
#define ENGINETEST_RENDEREROPENGL_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <RenderingSystem.h>
#include <Camera.h>
#include <vector>
#include "RenderableOpenGL.h"
#include "RenderableFactoryOpenGL.h"

class RendererOpenGL : public RenderingSystem {
private:
    void logSystemInformation();
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Camera* camera = new Camera();
    glm::mat4x4 projection;
    SDL_GLContext gl_context = nullptr;
    std::vector<RenderableOpenGL*> renderables;
    RenderableFactoryOpenGL *renderableFactoryOpenGl = new RenderableFactoryOpenGL();

    RendererOpenGL()=default;
    ~RendererOpenGL()=default;

    void init() override;
    void destroy() override;
    void render() override;
    void cleanScreen() override;
};


#endif //ENGINETEST_RENDEREROPENGL_H
