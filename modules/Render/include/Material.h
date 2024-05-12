#ifndef ENGINETEST_MATERIAL_H
#define ENGINETEST_MATERIAL_H

#include <string>
#include <SDLAPI.h>
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

    UnsignedInteger16 albedoUBO = UNSIGNED_INTEGER_MAX_16;
    UnsignedInteger16 metalicUBO = UNSIGNED_INTEGER_MAX_16;
    UnsignedInteger16 roughnessUBO = UNSIGNED_INTEGER_MAX_16;
    UnsignedInteger16 normalUBO = UNSIGNED_INTEGER_MAX_16;
    UnsignedInteger16 heightUBO = UNSIGNED_INTEGER_MAX_16;
    UnsignedInteger16 ambientOcclusionUBO = UNSIGNED_INTEGER_MAX_16;

    void virtual prepareMaterial(Renderable*);
    void virtual setTextures();
    explicit Material(const char* _name, Shader* _shader) { this->name = _name; this->shader = _shader; };
    ~Material() = default;
};

#endif //ENGINETEST_MATERIAL_H
