#ifndef ENGINETEST_PARALLAXMAPPINGSHADER_H
#define ENGINETEST_PARALLAXMAPPINGSHADER_H

#include <Shader.h>

class Light;
class OpenGLAPI;
class ParallaxMappingShader : public Shader {
public:
    Light* ambient = nullptr;
    Light* diffuse = nullptr;
    Light* specular = nullptr;

    Float heightScale = 0.0;

    Integer32 heightScaleUniform = INTEGER_MAX_32;
    Integer32 ambientColorUBO = INTEGER_MAX_32;
    Integer32 diffuseColorUBO = INTEGER_MAX_32;
    Integer32 specularColorUBO = INTEGER_MAX_32;

    Integer32 lightPositionUBO = INTEGER_MAX_32;
    Integer32 viewPositionUBO = INTEGER_MAX_32;

    ParallaxMappingShader();
    ~ParallaxMappingShader();
    void findUniformVariables(OpenGLAPI*) override;
    void useUniformVariables(RenderingSystem*, OpenGLAPI*, Renderable*) override;
};


#endif //ENGINETEST_PARALLAXMAPPINGSHADER_H
