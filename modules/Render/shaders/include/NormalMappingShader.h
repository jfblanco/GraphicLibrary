#ifndef ENGINETEST_NORMALMAPPINGSHADER_H
#define ENGINETEST_NORMALMAPPINGSHADER_H

#include <ShaderOpenGL.h>

class Light;
class NormalMappingShader : public ShaderOpenGL {
public:
    Light* ambient = nullptr;
    Light* diffuse = nullptr;
    Light* specular = nullptr;

    Sint16 ambientColor = SDL_MAX_SINT16;
    Sint16 diffuseColor = SDL_MAX_SINT16;
    Sint16 specularColor = SDL_MAX_SINT16;

    Sint16 lightPosition = SDL_MAX_SINT16;
    Sint16 viewPosition = SDL_MAX_SINT16;

    NormalMappingShader();
    ~NormalMappingShader();
    void findUniformVariables() override;
    void useUniformVariables(RenderingSystem*, Renderable*) override;
};


#endif //ENGINETEST_NORMALMAPPINGSHADER_H
