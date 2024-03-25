#ifndef ENGINETEST_TEXTURESHADER_H
#define ENGINETEST_TEXTURESHADER_H

#include <ShaderOpenGL.h>

class TextureShader : public ShaderOpenGL {
public:
    TextureShader() = default;
    ~TextureShader() = default;

    void useUniformVariables(RenderingSystem*, Renderable*) override;
};


#endif //ENGINETEST_TEXTURESHADER_H
