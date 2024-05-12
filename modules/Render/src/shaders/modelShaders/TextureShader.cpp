#include <TextureShader.h>
#include <OpenGLAPI.h>

void TextureShader::useUniformVariables(RenderingSystem* _renderingSystem, OpenGLAPI* _openGlApi, Renderable* _renderable) {
    Shader::useUniformVariables(_renderingSystem, _openGlApi, _renderable);
}
