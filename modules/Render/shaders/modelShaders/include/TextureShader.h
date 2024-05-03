#ifndef ENGINETEST_TEXTURESHADER_H
#define ENGINETEST_TEXTURESHADER_H

#include <Shader.h>

class TextureShader : public Shader {
public:
    TextureShader() = default;
    ~TextureShader() = default;

    void useUniformVariables(RenderingSystem*, Renderable*);
};


#endif //ENGINETEST_TEXTURESHADER_H
