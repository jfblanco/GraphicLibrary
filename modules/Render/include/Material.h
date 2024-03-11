#ifndef ENGINETEST_MATERIAL_H
#define ENGINETEST_MATERIAL_H

#include <string>
#include "ShaderOpenGL.h"

class Shader;
class Material {
public:
    ShaderOpenGL *shader;
    std::string name;

    explicit Material(const char* _name, ShaderOpenGL* _shader) { this->shader = _shader; this->name = _name;};
    ~Material() = default;
};

#endif //ENGINETEST_MATERIAL_H
