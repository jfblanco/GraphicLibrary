#ifndef ENGINETEST_PARALLAXMAPPINGSHADER_H
#define ENGINETEST_PARALLAXMAPPINGSHADER_H

#include <ShaderOpenGL.h>

class Light;
class ParallaxMappingShader : public ShaderOpenGL {
public:
    Light* ambient = nullptr;
    Light* diffuse = nullptr;
    Light* specular = nullptr;

    GLfloat heightScale = 0.0;

    Sint16 heightScaleUniform = SDL_MAX_SINT16;
    Sint16 ambientColor = SDL_MAX_SINT16;
    Sint16 diffuseColor = SDL_MAX_SINT16;
    Sint16 specularColor = SDL_MAX_SINT16;

    Sint16 lightPosition = SDL_MAX_SINT16;
    Sint16 viewPosition = SDL_MAX_SINT16;

    ParallaxMappingShader();
    ~ParallaxMappingShader();
    void findUniformVariables() override;
    void useUniformVariables(RenderingSystem*, Renderable*) override;
};


#endif //ENGINETEST_PARALLAXMAPPINGSHADER_H
