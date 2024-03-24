#ifndef ENGINETEST_NORMALSHADER_H
#define ENGINETEST_NORMALSHADER_H

#include <ShaderOpenGL.h>
#include "RenderableOpenGL.h"
#include <SDL2/SDL.h>

class NormalShader : public ShaderOpenGL {
public:
    NormalShader() = default;
    ~NormalShader() = default;
};


#endif //ENGINETEST_NORMALSHADER_H
