#ifndef ENGINETEST_RENDERABLE_OPENGL_H
#define ENGINETEST_RENDERABLE_OPENGL_H

#include <Renderable.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class MaterialOpenGL;
class ShaderManager;
class RenderableOpenGL {
public:
    Renderable *renderable = nullptr;
    MaterialOpenGL *materialOpenGL = nullptr;
    Uint16 vao = SDL_MAX_UINT16;
    Uint16 vertexVBO = SDL_MAX_UINT16;
    Uint16 normalVBO = SDL_MAX_UINT16;
    Uint16 tangentVBO = SDL_MAX_UINT16;
    Uint16 bitangentVBO = SDL_MAX_UINT16;
    Uint16 textureVBO = SDL_MAX_UINT16;
    Uint16 indexVBO = SDL_MAX_UINT16;

    explicit RenderableOpenGL(Renderable *_renderable) { this->renderable = _renderable; };
    void prepareMaterial(ShaderManager*);
    ~RenderableOpenGL() = default;

};

#endif //ENGINETEST_RENDERABLE_OPENGL_H
