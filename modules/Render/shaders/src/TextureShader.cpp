#include "../include/TextureShader.h"

void TextureShader::useUniformVariables(RenderingSystem* _renderingSystem, Renderable* _renderable) {
    ShaderOpenGL::useUniformVariables(_renderingSystem, _renderable);
}
