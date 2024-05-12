#ifndef ENGINETEST_LIGHTNINGSHADER_H
#define ENGINETEST_LIGHTNINGSHADER_H

#include <Shader.h>
#include <glm/glm.hpp>

class Light;
class OpenGLAPI;
class LightningShader : public Shader {
public:
    LightningShader() = default;
    ~LightningShader() = default;

    Light* ambient = nullptr;
    Light* diffuse = nullptr;
    Light* specular = nullptr;

    Integer32 ambientColorUBO = INTEGER_MAX_32;
    Integer32 diffuseColorUBO = INTEGER_MAX_32;
    Integer32 specularColorUBO = INTEGER_MAX_32;

    Integer32 lightPositionUBO = INTEGER_MAX_32;
    Integer32 viewPositionUBO = INTEGER_MAX_32;

    void findUniformVariables(OpenGLAPI*) override;
    void useUniformVariables(RenderingSystem*, OpenGLAPI*, Renderable*) override;
};


#endif //ENGINETEST_LIGHTNINGSHADER_H
