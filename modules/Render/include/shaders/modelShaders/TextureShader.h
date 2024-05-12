#ifndef ENGINETEST_TEXTURESHADER_H
#define ENGINETEST_TEXTURESHADER_H

#include <Shader.h>

class TextureShader : public Shader {
public:
    TextureShader() = default;
    ~TextureShader() = default;

    void useUniformVariables(RenderingSystem*, OpenGLAPI*, Renderable*) override;
};


#endif //ENGINETEST_TEXTURESHADER_H
