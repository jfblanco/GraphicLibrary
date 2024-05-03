#ifndef ENGINETEST_SHADER_H
#define ENGINETEST_SHADER_H

#include "../include/Shader.h"
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class RenderingSystem;
class Texture;
class Renderable;
class Shader {
public:
    std::string name;

    GLuint shaderProgram = 0;
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;

    Sint16 projectionModelViewUniform = SDL_MAX_UINT16;
    Sint16 modelMatrixUniform = SDL_MAX_UINT16;
    Sint16 viewMatrixUniform = SDL_MAX_UINT16;
    Sint16 vertexAttribute = SDL_MAX_UINT16;
    Sint16 normalAttribute = SDL_MAX_UINT16;
    Sint16 uvCoordAttribute = SDL_MAX_UINT16;
    Sint16 tangentAttribute = SDL_MAX_UINT16;
    Sint16 bitangentAttribute = SDL_MAX_UINT16;

    Sint16 albedoUBO = SDL_MAX_UINT16;
    Sint16 normalUBO = SDL_MAX_UINT16;
    Sint16 heightUBO = SDL_MAX_UINT16;
    Sint16 ambientOcclusionUBO = SDL_MAX_UINT16;
    Sint16 roughtnessOcclusionUBO = SDL_MAX_UINT16;
    Sint16 metallicUBO = SDL_MAX_UINT16;

    Shader() = default;
    ~Shader() = default;

    virtual void findUniformVariables();
    virtual void useUniformVariables(RenderingSystem*, Renderable*);
    virtual void findVertexAttributeVariables();
};

#endif //ENGINETEST_SHADER_H
