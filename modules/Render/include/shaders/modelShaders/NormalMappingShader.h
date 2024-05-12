#ifndef ENGINETEST_NORMALMAPPINGSHADER_H
#define ENGINETEST_NORMALMAPPINGSHADER_H

#include <Shader.h>

class Light;
class OpenGLAPI;
class NormalMappingShader : public Shader {
public:
    Light* ambient = nullptr;
    Light* diffuse = nullptr;
    Light* specular = nullptr;

    Integer32 ambientColorUBO = INTEGER_MAX_32;
    Integer32 diffuseColorUBO = INTEGER_MAX_32;
    Integer32 specularColorUBO = INTEGER_MAX_32;

    Integer32 lightPositionUBO = INTEGER_MAX_32;
    Integer32 viewPositionUBO = INTEGER_MAX_32;

    NormalMappingShader();
    ~NormalMappingShader();
    void findUniformVariables(OpenGLAPI*) override;
    void useUniformVariables(RenderingSystem*, OpenGLAPI*, Renderable*) override;
};


#endif //ENGINETEST_NORMALMAPPINGSHADER_H
