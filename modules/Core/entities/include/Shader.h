#ifndef ENGINETEST_SHADER_H
#define ENGINETEST_SHADER_H

#include <string>

class RenderingSystem;
class Texture;
class Renderable;
class Shader {
public:
    std::string name;

    virtual void findUniformVariables()=0;
    virtual void useUniformVariables(RenderingSystem*, Renderable*)=0;
    virtual void findVertexAttributeVariables()=0;
};

#endif //ENGINETEST_SHADER_H
