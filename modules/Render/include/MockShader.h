#ifndef ENGINETEST_MOCKSHADER_H
#define ENGINETEST_MOCKSHADER_H

#include "Shader.h"

class MockShader : public Shader {
public:
    void findUniformVariables() { };
    void useUniformVariables(RenderingSystem*, Renderable*) { };
    void findVertexAttributeVariables() { };
};


#endif //ENGINETEST_MOCKSHADER_H
