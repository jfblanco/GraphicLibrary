#ifndef ENGINETEST_MATERIAL_H
#define ENGINETEST_MATERIAL_H

#include <string>
#include <SDL2/SDL.h>
#include "Shader.h"

class Shader;
class Renderable;
class Material {
public:
    Shader *shader = nullptr;
    std::string name;
    Texture *albedo = nullptr;
    Texture *metal = nullptr;
    Texture *roughness = nullptr;
    Texture *normal = nullptr;
    Texture *height = nullptr;
    Texture *ambientOcclusion = nullptr;

    Uint16 albedoUBO = SDL_MAX_UINT16;
    Uint16 metalicUBO = SDL_MAX_UINT16;
    Uint16 roughnessUBO = SDL_MAX_UINT16;
    Uint16 normalUBO = SDL_MAX_UINT16;
    Uint16 heightUBO = SDL_MAX_UINT16;
    Uint16 ambientOcclusionUBO = SDL_MAX_UINT16;

    void virtual prepareMaterial(Renderable*);
    void virtual setTextures();
    explicit Material(const char* _name, Shader* _shader) { this->name = _name; this->shader = _shader; };
    ~Material() = default;
};

#endif //ENGINETEST_MATERIAL_H
