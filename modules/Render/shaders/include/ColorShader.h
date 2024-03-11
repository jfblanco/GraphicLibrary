#ifndef ENGINETEST_COLORSHADER_H
#define ENGINETEST_COLORSHADER_H

#include <ShaderOpenGL.h>
#include "RenderableOpenGL.h"
#include <SDL2/SDL.h>

class ColorShader : public ShaderOpenGL {
public:
    ColorShader() = default;
    ~ColorShader() = default;

    Sint16 projectionModelViewUniform;
    Sint16 vertexAttribute;
    Sint16 normalAttribute;
    Sint16 uvCoordAttribute;

    void findUniformVariables() override;
    void useUniformVariables(RenderingSystem*) override;
    void findVertexAttributeVariables() override;
};


#endif //ENGINETEST_COLORSHADER_H
