#ifndef ENGINETEST_MATERIAL_H
#define ENGINETEST_MATERIAL_H

#include <string>

class Texture;
class Material {
public:
    std::string name;
    Texture *albedo;
    Texture *metal;
    Texture *roughness;
    Texture *normal;
    Texture *ambientOcclusion;

    explicit Material(const char* _name) { this->name = _name; };
    ~Material() = default;
};

#endif //ENGINETEST_MATERIAL_H
