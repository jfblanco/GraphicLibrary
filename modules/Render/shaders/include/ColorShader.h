#ifndef ENGINETEST_COLORSHADER_H
#define ENGINETEST_COLORSHADER_H

#include <ShaderOpenGL.h>
#include "RenderableOpenGL.h"
#include <SDL2/SDL.h>

class ColorShader : public ShaderOpenGL {
public:
    ColorShader() = default;
    ~ColorShader() = default;
};


#endif //ENGINETEST_COLORSHADER_H
