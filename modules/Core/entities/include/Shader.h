#ifndef ENGINETEST_SHADER_H
#define ENGINETEST_SHADER_H

#include <string>

class RenderingSystem;
class Texture;
class Shader {
public:
    std::string name;
    Texture *albedo;
    Texture *metal;
    Texture *roughness;
    Texture *normal;
    Texture *ambientOcclusion;

    virtual void findUniformVariables()=0;
    virtual void useUniformVariables(RenderingSystem*)=0;
    virtual void findVertexAttributeVariables()=0;
};

#endif //ENGINETEST_SHADER_H
