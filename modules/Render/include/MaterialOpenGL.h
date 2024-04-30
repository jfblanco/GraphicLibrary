#ifndef ENGINETEST_MATERIALOPENGL_H
#define ENGINETEST_MATERIALOPENGL_H

#include <string>
#include <Material.h>
#include <SDL2/SDL.h>
#include "ShaderOpenGL.h"

class Shader;
class RenderableOpenGL;
class MaterialOpenGL : public Material {
public:
    ShaderOpenGL *shaderOpenGL = nullptr;
    Uint16 albedo = SDL_MAX_UINT16;
    Uint16 metalic = SDL_MAX_UINT16;
    Uint16 roughness = SDL_MAX_UINT16;
    Uint16 normal = SDL_MAX_UINT16;
    Uint16 height = SDL_MAX_UINT16;
    Uint16 ambientOcclusion = SDL_MAX_UINT16;

    void prepareMaterial(RenderableOpenGL*);
    void setTextures();
    explicit MaterialOpenGL(const char* _name, ShaderOpenGL* _shader) : Material(_name) { this->shaderOpenGL = _shader; };
    ~MaterialOpenGL() = default;
};

#endif //ENGINETEST_MATERIALOPENGL_H
